#pragma once

#include <vector>
#include <set>
#include <random>

#include "hex.hpp"
#include "player.hpp"
#include "rng.hpp"
#include "ui.hpp"
#include "tech.hpp"
#include "board.hpp"

struct PlayerAction {
    int cost;
    std::function<bool()> act_fn;
};

static const std::string ANNEX = "annex";
static const std::string ATTACK = "attack";
static const std::string SWORD = "sword";
static const std::string SHIELD = "shield";
static const std::string IMPROVE = "improve";
static const std::vector<std::string> action_strings = {ANNEX, ATTACK, SWORD, SHIELD, IMPROVE};

struct Game {
    std::vector<GameHex> hexes;
    Board board = Board();
    std::vector<Player> players;
    int current_player_idx = 0; 
    int win_gold = 30;
    bool ended = false;
    const static std::vector<double> prod_distribution;
    const static std::vector<int> prod_values;
    Randomizer rng = Randomizer();

    std::map<std::string, PlayerAction> actions = {
        {ANNEX, PlayerAction(5, [this](){return this->annex();})},
        {SWORD, PlayerAction(5, [this](){return this->add_sword();})},
        {SHIELD, PlayerAction(5, [this](){return this->add_shield();})},
        {ATTACK, PlayerAction(0, [this](){return this->attack();})},
        {IMPROVE, PlayerAction(0, [this](){return this->improve();})},
    };

    Game(int size, int players);
    bool next_turn();
    void print();

    bool annex();
    bool add_shield();
    bool add_sword();
    bool attack();
    bool improve();

    // bool research(Tech& tech);

    // const ACTION parse_action() const;
    const Tech& get_tech() const;
    GameHex& get_hex();

    Player& current_player() const;
    const void next_player();

    bool accessible(const GameHex& hex, int dist=1) const;
};
