#include "game.hpp"

const std::vector<double> Game::prod_distribution = {0.85, 0.12, 0.03};
const std::vector<int> Game::prod_values = {0, 1, 2};

Game::Game(int size, int players) {
    for (int i = 0; i < players; i++) {
        this->players.emplace_back(Player());
    }

    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            if (abs(i + j) > size) {
                continue;
            }
            int owner = NO_PLAYER;
            int prod = rng.rand_choose(prod_distribution, prod_values);
            if (i == 0 && j == -2) {
                owner = 1;
                prod = 1;
            } else if (i == 0 && j == 2) {
                owner = 0;
                prod = 1;
            }
            board.hexes.emplace_back(GameHex(i+size, j+size, prod, owner));
        }
    }
}

// returns whether the game is still ongoing
bool Game::next_turn() {
    Player& player = current_player();
    int& gold = player.gold;
    // calculate gold production
    for (auto& hex: board.hexes) {
        if (hex.owner == current_player_idx) {
            const int prod = hex.production;
            gold += prod;
        }
    }
    if (gold > win_gold) {
        std::cout << "Player " << current_player_idx << " wins!\n";
        ended = true;
        return false;
    }
    std::set<std::string> free_actions = {ANNEX, SWORD, SHIELD};


    std::string action_str;
    while (1)
    {
        this->print();
        std::cout << "Valid Actions\n";
        for (const auto& [name, action] : actions) {
            std::string cost = (free_actions.find(name) == free_actions.end()) ? actions[name].cost_description : "free";
            std::cout << name << " (cost: " << cost << ")" << " - " << action.description << "\n";
        }
        std::cout << "end\n";
        if ((action_str = get_input("Action: ")) == "end") {
            break;
        }
        this->print();
        if (actions.find(action_str) == actions.end()) {
            std::cout << "Invalid action.\n";
            continue;
        }
        PlayerAction& action = actions[action_str];
        bool is_free = free_actions.find(action_str) != free_actions.end();
        if (!is_free && gold < action.cost) {
            std::cout << "Not enough gold.\n";
            continue;
        } 
        free_actions.erase(action_str);
        if (!is_free) {
            gold -= action.cost;
        }
        std::string status_str = action.act_fn() ? "succeeded" : "failed";
        std::cout << action_str << " " << status_str << ". Press enter to continue.\n";
        std::cin.get();
    }

    for (auto& hex : board.hexes) {
        if (hex.owner == 1 - current_player_idx) {
            next_player();
            return true;
        }
    }
    std::cout << "Player " << current_player_idx << " wins.\n";
    turn++;
    return false;
}

bool Game::annex()
{
    std::cout << "Annex hex.\n";
    GameHex& hex = Game::get_hex();
    if (accessible(hex) && hex.owner == NO_PLAYER) {
        hex.owner = current_player_idx;
        return true;
    }
    return false;
}


bool Game::add_sword()
{
    std::cout << "On hex\n";
    GameHex& hex = Game::get_hex();
    if (hex.owner == current_player_idx && hex.swords < 3) {
        hex.swords += 1;
        return true;
    }
    return false;
}


bool Game::add_shield()
{
    std::cout << "Add defender to hex.\n";
    GameHex& hex = Game::get_hex();
    if (hex.owner == current_player_idx && hex.shields < 3) {
        hex.shields += 1;
        return true;
    }
    return false;
}

bool Game::attack()
{
    std::cout << "Attack!.\n";
    std::cout << "From hex\n";
    GameHex& attacker = Game::get_hex();
    std::cout << "To hex\n";
    GameHex& defender = Game::get_hex();
    if (attacker.owner != current_player_idx 
        || !attacker.is_neighbor(defender)
        || attacker.swords == 0) {
        return false;
    }
    attacker.swords -= 1;
    if (defender.shields > 0) {
        defender.shields -= 1;
    } else {
        defender.owner = (defender.owner == NO_PLAYER) ? current_player_idx : NO_PLAYER;
        defender.swords = 0;
    }
    return true;
}

bool Game::improve()
{
    std::cout << "Improve hex.\n";
    GameHex& hex = Game::get_hex();
    if (hex.owner == current_player_idx
        && hex.production < hex.max_production
        && hex.shields >= 2) {
        hex.production += 1;
        hex.shields -= 2;
        return true;
    }
    return false;
}

const Tech& Game::get_tech() const {
    std::string tech_name = get_input("Input tech: ");
    Tech& tech = techs.find(tech_name)->second;
    return tech;
}

GameHex& Game::get_hex() {
    while (1) {
        std::string hex_name = get_input("coords: ");
        for (GameHex& hex : board.hexes) {
            if (hex.pos() == hex_name) {
                return hex;
            }
        }
        std::cout << "Invalid hex.\n";
    }
}

Player& Game::current_player() const
{
    return const_cast<Player&>(players.at(current_player_idx));
}

const void Game::next_player() {
    current_player_idx = (current_player_idx + 1) % players.size();
}


void Game::print() {
    clear_terminal();
    board.print();
    for (int i = 0, n = players.size(); i < n; i++) {
        int income = 0;
        for (const GameHex& hex : board.hexes) {
            if (hex.owner == i) {
                income += hex.production;
            }
        }
        std::string indicator = (i == current_player_idx) ? ">" : " ";
        std::cout << PLAYER_COLORS.at(i) << indicator << players.at(i);
        std::cout << " [+" << income << "G]";
        std::cout << RESET << "\n";
    }
}

bool Game::accessible(const GameHex& hex, int dist) const {
    for (const GameHex& h : board.hexes) {
        if (h.owner == current_player_idx && h.distance(hex) <= dist) {
            return true;
        }
    }
    return false;
}