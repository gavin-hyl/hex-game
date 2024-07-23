#include "game.hpp"

const std::vector<double> Game::prod_distribution = {0.5, 0.25, 0.15, 0.1};
const std::vector<int> Game::prod_values = {0, 1, 3, 5};

Game::Game(int size, int players) {
    for (int i = 0; i < players; i++) {
        this->players.emplace_back(Player());
    }

    for (int i = -size; i <= size; i++) {
        for (int j = -size-i; j <= size-i; j++) {
            int prod = random_distribution_choose(prod_distribution, prod_values);
            this->board.emplace_back(GameHex(i, j, prod));
        }
    }
}


bool Game::next_turn() {
    current_player_idx = (current_player_idx + 1) % players.size();
    Player& current_player = players.at(current_player_idx);

    // calculate gold production
    for (auto hex_p: current_player.owned_hexes) {
        const int prod = hex_p->production;
        current_player.gold += prod;
        if (current_player.researched(EconT0) && prod > 0) {
            current_player.gold += 1;
        }
        if (current_player.researched(EconT1) && prod > 0) {
            current_player.gold += 1;
        }
        if (current_player.researched(EconT2)) {
            current_player.gold += 1;
        }
    }

    Action action;
    while ((action = parse_action()) != Action::END_TURN) {
        // check for victory
        if (current_player.researched(EndGame)) {
            ended = true;
            return true;
        }

        // research tech
        if (action == Action::RESEARCH) {
            Tech tech = get_tech();
            research(tech);
        } else if (action == Action::ATTACK) {
            GameHex hex = get_hex();
            attack(hex);
        } else if (action == Action::DEFEND) {
            GameHex hex = get_hex();
            defend(hex);
        } else if (action == Action::ANNEX) {
            GameHex hex = get_hex();
            annex(hex);
        }
        
    }
    return false;
}

void Game::attack(GameHex &defender)
{

}

void Game::research(Tech &tech)
{
}

void Game::defend(GameHex &hex)
{
}

void Game::annex(GameHex &hex)
{
    Player& current_player = players.at(current_player_idx);
    if (current_player.gold < hex.production) {
        return;
    }
}

const Game::Action Game::parse_action() const {
    std::string action = get_input("Input action: ");
    if (action == "attack") {
        return Game::ATTACK;
    } else if (action == "defend") {
        return Game::DEFEND;
    } else if (action == "research") {
        return Game::RESEARCH;
    } else {
        return Game::END_TURN;
    }
}

const Tech& Game::get_tech() const {
    std::string tech_name = get_input("Input tech: ");
    Tech& tech = techs.find(tech_name)->second;
    return tech;
}

const GameHex& Game::get_hex() const {
    return board.at(0);
}
