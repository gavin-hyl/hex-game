#include "hex.hpp"

#include <iostream>


Hex::Hex(int u, int v, int w)
    : u(u), v(v), w(w) {
        assert(u + v + w == 0);
}

Hex::Hex(int u, int v)
    : u(u), v(v), w(-u - v) {}

int Hex::distance(const struct Hex& b) const {
    return std::max({abs(u - b.u), abs(v - b.v), abs(w - b.w)});
}

bool Hex::is_neighbor(const struct Hex& b) const {
    return distance(b) == 1;
}

std::vector<Hex> Hex::neighbors() const {
    return {
        Hex(u + 1, v - 1), Hex(u + 1, v), Hex(u, v + 1),
        Hex(u - 1, v + 1), Hex(u - 1, v), Hex(u, v - 1)
    };
}

GameHex::GameHex(int u, int v, int production)
    : Hex(u, v), production(production){ }