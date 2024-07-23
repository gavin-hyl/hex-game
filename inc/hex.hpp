#pragma once

#include <cassert>
#include <vector>
#include <algorithm>

struct Hex
{
    const int u;
    const int v;
    const int w;

    Hex(int u, int v, int w);

    Hex(int u, int v);
    
    int distance(const struct Hex& b) const;

    bool is_neighbor(const struct Hex& b) const;

    std::vector<Hex> neighbors() const;
};


struct GameHex : public Hex
{
    const int production = 0;
    static const std::vector<double> production_weights;
    int defenders = 0;
    int attackers = 0;
    GameHex(int u, int v, int production);
};
