#pragma once

#include <cassert>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include "player.hpp"

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
    int production = 0;
    int max_production = 3;
    int shields = 0;
    int max_shields = 3;
    int swords = 0;
    int max_swords = 3;
    int owner = 0;
    GameHex(int u, int v, int production=0, int owner=-1);
};
