#include "hex.hpp"

// odd-q offset coordinates
Hex::Hex(int u, int v, int w)
    : u(u), v(v), w(w), row(v + (u - (u & 1)) / 2), col(u) {
    if (u + v + w != 0) {
        throw std::invalid_argument("u + v + w must be 0");
    }
}

Hex::Hex(int u, int v)
    : Hex(u, v, -u-v) {}

int Hex::distance(const struct Hex& b) const {
    return (std::abs(u - b.u) + std::abs(v - b.v) + std::abs(w - b.w)) / 2;
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

std::string Hex::pos() const {
    std::stringstream ss;
    ss << std::string(1, (u +'a')) << "-" << v;
    return ss.str();
}


GameHex::GameHex(int u, int v, int production, int owner)
    : Hex(u, v), production(production), owner(owner){ }