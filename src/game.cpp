#include "game.hpp"

const std::vector<double> Game::prod_distribution = {0.85, 0.12, 0.03};
const std::vector<gold_t> Game::prod_values = {0, 1, 2};
const std::vector<HexPos> Game::capitals = {HexPos(0, -2), HexPos(0, 2)};

Game::Game(int size, int players) {
    for (int i = 0; i < players; i++) {
        this->players.emplace_back(Player());
    }

    board = Board(size);
    // generate board with player-specific information
    for (player_id_t i = 0; i < players; i++) {
        HexPos capital_pos = capitals.at(i);
        capital_pos.u += size;
        capital_pos.v += size;
        GameHex& capital_hex = board.get_hex(capital_pos);
        capital_hex.owner = i;
        capital_hex.capital = i;
        // std::vector<GameHex&> ring1 = board.get_ring(capital_hex.pos, 1);
        // std::vector<GameHex&> ring2 = board.get_ring(capital_hex.pos, 2);
        for (int i = 0; i < 3; i++) {

        }
    }
}

// returns whether the game is still ongoing
bool Game::next_turn() {
    Player& player = current_player();
    gold_t& gold = player.gold;
    // calculate gold production
    gold += player_prodution(current_id);

    std::string action_str;
    while (1)
    {
        this->print();
        std::string response = get_input("Input hex coords/help/end.\n>>>");
        // first check for special commands
        if (response == "end") {
            break;
        } else if (response == "help") {
            std::cout << "Actions:\n";
            for (const auto& [name, action] : actions) {
                std::cout << COLOR(BOLD, name) << ": " << action.description << "\n";
                std::cout << "Cost: " << action.cost.to_string() << "\n";
            }
            wait();
            continue;
        }
        // no special command, so it must be a hex
        try {
            selected_hex = &get_hex(response);
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            continue;
        }
        // check for valid actions
        std::vector<PlayerAction> valid_actions;
        for (const auto& action : actions) {
            if (affordable(action.second.cost) && action.second.check()) {
                valid_actions.push_back(action.second);
            }
        }
        if (valid_actions.size() == 0) {
            std::cout << "No valid actions.\n";
            continue;
        }
        std::cout << "Valid actions:\n";
        for (int i = 0, n = valid_actions.size(); i < n; i++) {
            std::cout << i << ". " << valid_actions[i].description << "\n";
        }
        // get action and perform it
        int action_idx = std::stoi(get_input("Input action: "));
        valid_actions[action_idx].act();
        incur(valid_actions[action_idx].cost);
    }

    next_player();
    turn++;
    return false;
}

bool Game::check_annex()
{
    return (selected_hex->owner == NO_PLAYER
            && accessible(*selected_hex, 1));
}

void Game::annex()
{
   selected_hex->owner = current_id;
}

bool Game::check_add_sword()
{
    return (selected_hex->owner == current_id)
            && (selected_hex->swords < selected_hex->max_swords);
}

void Game::add_sword()
{
    selected_hex->swords += 1;
}


bool Game::check_add_shield()
{
    return (selected_hex->owner == current_id)
            && (selected_hex->shields < selected_hex->max_shields);
}

void Game::add_shield()
{
    selected_hex->shields += 1;
}

bool Game::check_attack()
{
    if (selected_hex->owner != current_id) {
        return false;
    }

    for (GameHex& hex : board.hexes) {
        if (hex.owner != current_id
            && hex.owner != NO_PLAYER
            && hex.pos.is_neighbor(selected_hex->pos)) {
            return true;
        }
    }
    return false;
}

void Game::attack()
{
    std::cout << "Attack hex\n";
    GameHex& other_selected_hex = get_hex();
    if (other_selected_hex.shields == 0) {
        other_selected_hex.owner = current_id;
    } else {
        other_selected_hex.shields -= 1;
    }
}

bool Game::check_improve()
{
    return (selected_hex->owner == current_id
            && selected_hex->production < selected_hex->max_production);
}

void Game::improve()
{
    selected_hex->production += 1;
}


bool Game::affordable(const ActionCost &cost) const
{
    const Player& player = current_player();
    return (player.gold >= cost.gold
            && selected_hex->swords >= cost.swords
            && selected_hex->shields >= cost.shields);
}

void Game::incur(const ActionCost &cost)
{
    Player& player = current_player();
    player.gold -= cost.gold;
    selected_hex->swords -= cost.swords;
    selected_hex->shields -= cost.shields;
}

const Tech& Game::get_tech() const {
    std::string tech_name = get_input("Input tech: ");
    Tech& tech = techs.find(tech_name)->second;
    return tech;
}

GameHex& Game::get_hex(std::string coords) {
    if (coords == "") {
        coords = get_input("coords: ");
    }
    for (GameHex& hex : board.hexes) {
        if (hex.pos.str() == coords) {
            return hex;
        }
    }
    throw std::invalid_argument("Invalid hex coords.");
}

Player& Game::current_player() const
{
    return const_cast<Player&>(players.at(current_id));
}

const void Game::next_player() {
    current_id = (current_id + 1) % players.size();
}

gold_t Game::player_prodution(player_id_t id) const
{
    gold_t prod = BASE_PROD;
    for (const GameHex& hex : board.hexes) {
        if (hex.owner == id) {
            prod += hex.production;
        }
    }
    return prod;
}

void Game::print() {
    // clear_terminal();
    board.print();
    std::cout << "Turn " << turn << "\n";
    std::cout << "Goal: " << win_gold << "G\n";
    for (int i = 0, n = players.size(); i < n; i++) {
        std::string indicator = (i == current_id) ? ">" : " ";
        std::cout << PLAYER_COLORS.at(i) << indicator << players.at(i);
        std::cout << " [+" << player_prodution(i) << "G]";
        std::cout << RESET << "\n";
    }
}

bool Game::accessible(const GameHex& hex, int dist) const {
    for (const GameHex& h : board.hexes) {
        if (h.owner == current_id && h.pos.distance(hex.pos) <= dist) {
            return true;
        }
    }
    return false;
}