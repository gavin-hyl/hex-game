#pragma once

#include <vector>
#include <set>
#include <random>

#include "hex.hpp"
#include "player.hpp"
#include "rng.hpp"
#include "ui.hpp"
#include "tech.hpp"

struct Game {
    std::vector<GameHex> board;
    std::vector<Player> players;
    int current_player_idx = 0; 
    bool ended = false;
    const static std::vector<double> prod_distribution;
    const static std::vector<int> prod_values;

    enum Action {
        ANNEX,
        ATTACK,
        DEFEND,
        RESEARCH,
        END_TURN
    };


    Game(int size, int players);
    
    bool next_turn();

    void attack(GameHex& defender);
    void research(Tech& tech);
    void defend(GameHex& hex);
    void annex(GameHex& hex);

    const Action parse_action() const;
    const Tech& get_tech() const;
    const GameHex& get_hex() const;
};
