#pragma once

#include <cassert>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include "gamedefs.hpp"

struct HexPos
{
    // axial(cubic) coordinates
    int u;
    int v;
    int w;

    // odd-q offset coordinates
    int row;
    int col;

    HexPos(int u, int v, int w);

    HexPos(int u, int v);

    int distance(const HexPos& b) const;
    bool is_neighbor(const HexPos& b) const;

    bool operator==(const HexPos& b) const {
        return u == b.u && v == b.v;
    }

    std::vector<HexPos> neighbors() const;

    std::string str() const;
};


struct GameHex
{
    HexPos pos;
    gold_t production = 0;
    gold_t max_production = 3;
    shield_t shields = 0;
    shield_t max_shields = 3;
    sword_t swords = 0;
    sword_t max_swords = 3;
    player_id_t owner = 0;
    player_id_t capital = 0;
    GameHex(int u, int v, gold_t production=0, player_id_t owner=-1);
};
