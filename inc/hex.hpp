#pragma once

#include <cassert>
#include <vector>
#include <algorithm>

struct Hex
{
    // axial coordinates
    int u;
    int v;
    int w;

    // odd-r offset coordinates
    int row;
    int col;

    Hex(int u, int v, int w);

    Hex(int u, int v);

    int distance(const struct Hex& b) const;

    bool is_neighbor(const struct Hex& b) const;

    bool operator<(const Hex& b) const {
        return row < b.row || (row == b.row && col < b.col);
    }

    bool operator==(const Hex& b) const {
        return u == b.u && v == b.v && w == b.w;
    }

    std::vector<Hex> neighbors() const;
};


struct GameHex : public Hex
{
    int production = 0;
    int defenders = 0;
    int attackers = 0;
    GameHex(int u, int v, int production=0);
};
