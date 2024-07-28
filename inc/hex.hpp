#pragma once

#include <cassert>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include "gamedefs.hpp"

struct Hex
{
    // axial(cubic) coordinates
    int u;
    int v;
    int w;

    // odd-q offset coordinates
    int row;
    int col;

    Hex(int u, int v, int w);

    Hex(int u, int v);

    int distance(const struct Hex& b) const;

    bool is_neighbor(const struct Hex& b) const;

    bool operator<(const Hex& b) const {
        return row < b.row || (row == b.row && col < b.col);
    }

    std::vector<Hex> neighbors() const;

    std::string pos() const;
};


struct GameHex : public Hex
{
    gold_t production = 0;
    gold_t max_production = 3;
    shield_t shields = 0;
    shield_t max_shields = 3;
    sword_t swords = 0;
    sword_t max_swords = 3;
    player_id_t owner = 0;
    GameHex(int u, int v, gold_t production=0, player_id_t owner=-1);
};
