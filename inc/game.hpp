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

struct Game {
    std::vector<GameHex> hexes;
    Board board = Board();
    std::vector<Player> players;
    int current_player_idx = 0; 
    bool ended = false;
    const static std::vector<double> prod_distribution;
    const static std::vector<int> prod_values;

    enum ACTION {
        ANNEX,
        ATTACK,
        DEFEND,
        RESEARCH,
        END_TURN
    };

    const static std::map<ACTION, int> action_costs;

    Game(int size, int players);
    bool next_turn();
    void print();

    bool annex();
    bool add_shield();
    bool add_sword();
    bool attack();
    // bool research(Tech& tech);

    const ACTION parse_action() const;
    const Tech& get_tech() const;
    GameHex& get_hex();

    Player& current_player() const;
    const void next_player();

    bool accessible(const GameHex& hex, int dist=1) const;
};
