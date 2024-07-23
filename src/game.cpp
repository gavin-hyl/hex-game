#include "game.hpp"

const std::vector<double> Game::prod_distribution = {0.8, 0.15, 0.05};
const std::vector<int> Game::prod_values = {0, 1, 2};
const std::map<Game::ACTION, int> Game::action_costs = {
    {Game::ANNEX, 0},
    {Game::ATTACK, 1},
    {Game::DEFEND, 1},
    {Game::RESEARCH, 1},
    {Game::END_TURN, 0}
};

Game::Game(int size, int players) {
    for (int i = 0; i < players; i++) {
        this->players.emplace_back(Player());
    }

    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            if (abs(i + j) > size) {
                continue;
            }
            int owner = -1;
            if (i == 0 && j == -2) {
                owner = 1;
            } else if (i == 0 && j == 2) {
                owner = 0;
            }
            int prod = random_distribution_choose(prod_distribution, prod_values);
            this->hexes.emplace_back(GameHex(i+size, j+size, prod, owner));
        }
    }
    this->board = Board(this->hexes);
}


bool Game::next_turn() {
    Player& player = current_player();

    // calculate gold production
    for (auto& hex: hexes) {
        if (hex.owner != current_player_idx) {
            continue;
        }
        const int prod = hex.production;
        player.gold += prod;
    }
    if (player.gold > 30) {
        std::cout << "Player " << current_player_idx << " wins!\n";
        ended = true;
        return false;
    }

    std::string action;
    std::map<std::string, std::function<bool()>> actions = {
        {"annex", [this](){return this->annex();}},
        {"sword", [this](){return this->add_sword();}},
        {"shield", [this](){return this->add_shield();}},
        {"attack", [this](){return this->attack();}},
    };

    this->print();
    
    while ((action = get_input("Action: ")) != "end")
    {
        if (actions.find(action) != actions.end()) {
            if (actions[action]()) {
                std::cout << action << " succeeded.\n";
            } else {
                std::cout << action << " failed.\n";
            }
        } else {
            std::cout << "Invalid action.\n";
        }
        this->print();
    }

    next_player();
}

bool Game::annex()
{
    std::cout << "Annex hex.\n";
    GameHex& hex = Game::get_hex();
    if (accessible(hex) && hex.owner == -1) {
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
    }
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
        defender.owner = current_player_idx;
        defender.swords = 1;
    }
    return true;
}

const Tech& Game::get_tech() const {
    std::string tech_name = get_input("Input tech: ");
    Tech& tech = techs.find(tech_name)->second;
    return tech;
}

GameHex& Game::get_hex() {
    std::string hex_name = get_input("coords: ");
    for (GameHex& hex : hexes) {
        if (hex.pos() == hex_name) {
            return hex;
        }
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
    board.update_hexes(hexes);
    board.print();
    for (unsigned int i = 0; i < players.size(); i++) {
        if (i == current_player_idx) {
            std::cout << PLAYER_COLORS.at(i) << ">" << players.at(i) << RESET << "\n";
        } else {
            std::cout << PLAYER_COLORS.at(i) << players.at(i) << RESET << "\n";
        }
    }
}

bool Game::accessible(const GameHex& hex, int dist) const {
    for (const GameHex& h : hexes) {
        if (h.owner == current_player_idx && h.distance(hex) <= dist) {
            return true;
        }
    }
    return false;
}