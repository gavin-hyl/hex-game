#include "game.hpp"

const std::vector<double> Game::prod_distribution = {0.85, 0.12, 0.03};
const std::vector<gold_t> Game::prod_values = {0, 1, 2};
const std::vector<HexPos> Game::capitals_rel = {HexPos(0, -3), HexPos(0, 3)};

Game::Game(int size, int players) {
    for (int i = 0; i < players; i++) {
        this->players.emplace_back(Player());
    }

    for (const HexPos& capital_rel : capitals_rel) {
        capitals.push_back(HexPos(capital_rel.u + size, capital_rel.v + size));
    }

    board = Board(size);
    // generate board with player-specific information
    for (player_id_t i = 0; i < players; i++) {
        HexPos capital_pos = capitals.at(i);
        GameHex& capital_hex = *(board.get_hex(capital_pos));
        capital_hex.owner = i;
        capital_hex.capital = i;
        capital_hex.production = 3;
        auto ring1 = rng.rand_choose_noreplace(board.get_ring(capital_hex.pos, 1), 3);
        auto ring2 = rng.rand_choose_noreplace(board.get_ring(capital_hex.pos, 2), 3);
        for (GameHex* hex : ring1) {
            hex->production = 1;
        }
        for (GameHex* hex : ring2) {
            hex->production = 2;
        }
    }
    // populate the rest of the board with random production values
    for (GameHex& hex : board.hexes) {
        bool close_to_capital = false;
        for (const HexPos& capital_pos : capitals) {
            if (hex.pos.distance(capital_pos) <= 2) {
                close_to_capital = true;
                std::cout << "close\n";
                break;
            }
        }
        if (!close_to_capital) {
            hex.production = rng.rand_choose(prod_values, prod_distribution);
        }
    }
}

// returns whether the game is still ongoing
bool Game::next_turn() {
    Player& player = current_player();
    player.gold += player_prodution(current_id);

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
                std::cout << "Cost: " << action.cost.str() << "\n";
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
            wait();
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

    for (uint8_t i = 0; i < players.size(); i++) {
        if (i == current_id) {
            continue;
        }
        GameHex* capital_hex = board.get_hex(capitals.at(i));
        std::vector<GameHex*> frontier = {capital_hex};
        std::vector<GameHex*> visited;
        while (!frontier.empty())
        {
            GameHex* current_hex = frontier.front();
            frontier.erase(frontier.begin());
            visited.emplace_back(current_hex);
            for (GameHex* hex : board.get_ring(current_hex->pos, 1)) {
                if ((hex->owner == i) && (std::find(visited.begin(), visited.end(), hex) == visited.end())) {
                    frontier.emplace_back(hex);
                }
            }

            // testing
            for (GameHex* hex : frontier) {
                std::cout << hex->pos.str() << " ";
            }
            for (GameHex* hex : visited) {
                std::cout << hex->pos.str() << " ";
            }
        }
        for (GameHex& hex: board.hexes) {
            if ((std::find(visited.begin(), visited.end(), &hex) == visited.end())
                && (hex.owner == i)) {
                hex.owner = NO_PLAYER;
            }
        }
    }

    current_id = (current_id + 1) % players.size();
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
    if (other_selected_hex.owner == NO_PLAYER) {
        other_selected_hex.owner = current_id;
    } else if (other_selected_hex.shields == 0) {
        other_selected_hex.owner = NO_PLAYER;
    } else {
        other_selected_hex.shields -= 1;
    }
}

bool Game::check_improve()
{
    return (selected_hex->owner == current_id)
            && (selected_hex->production < selected_hex->max_production);
}

void Game::improve()
{
    selected_hex->production += 2;
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

inline Player& Game::current_player() const
{
    return const_cast<Player&>(players.at(current_id));
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
    clear_terminal();
    canvas.update(board.hexes);
    canvas.print();
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