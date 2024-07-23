#include "game.hpp"

const std::vector<double> Game::prod_distribution = {0.5, 0.25, 0.15, 0.1};
const std::vector<int> Game::prod_values = {0, 1, 3, 5};
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
            int prod = random_distribution_choose(prod_distribution, prod_values);
            this->hexes.emplace_back(GameHex(i+size, j+size, prod));
        }
    }
    this->board = Board(this->hexes);
}


bool Game::next_turn() {
    next_player();
    Player& player = current_player();

    // calculate gold production
    for (auto hex_p: player.owned_hexes) {
        const int prod = hex_p->production;
        player.gold += prod;
        if (player.researched(EconT0) && prod > 0) {
            player.gold += 1;
        }
        if (player.researched(EconT1) && prod > 0) {
            player.gold += 1;
        }
        if (player.researched(EconT2)) {
            player.gold += 1;
        }
    }

    // free attack
    if (player.researched(AttackT2)) {
    }

    // free defense
    if (player.researched(DefenseT2)) {
    }

    ACTION action;
    while ((action = parse_action()) != ACTION::END_TURN) {
        // check for victory
        if (player.researched(EndGame)) {
            ended = true;
            return true;
        }

        if (action == ACTION::RESEARCH) {
            Tech tech = get_tech();
            research(tech);
        } else if (action == ACTION::ATTACK) {
        } else if (action == ACTION::DEFEND) {
        } else if (action == ACTION::ANNEX) {
        }
        
    }
    return false;
}

void Game::attack(GameHex &defender)
{
    Player& current_player = players.at(current_player_idx);
    if (current_player.gold < ACTION::ATTACK) {
        return;
    }
    current_player.gold -= ACTION::ATTACK;
    defender.attackers += 1;
    current_player.gold -= defender.production;
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

const Game::ACTION Game::parse_action() const {
    std::string action = get_input("Input action: ");
    if (action == "attack") {
        return Game::ATTACK;
    } else if (action == "defend") {
        return Game::DEFEND;
    } else if (action == "research") {
        return Game::RESEARCH;
    }
    return Game::END_TURN;
}

const Tech& Game::get_tech() const {
    std::string tech_name = get_input("Input tech: ");
    Tech& tech = techs.find(tech_name)->second;
    return tech;
}

const GameHex& Game::get_hex() const {
    return hexes.at(0);
}

Player& Game::current_player() const
{
    return const_cast<Player&>(players.at(current_player_idx));
}

const void Game::next_player()
{
    current_player_idx = (current_player_idx + 1) % players.size();
}
