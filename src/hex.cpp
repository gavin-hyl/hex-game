#include "hex.hpp"

// odd-q offset coordinates
HexPos::HexPos(int u, int v, int w)
    : u(u), v(v), w(w), row(v + (u - (u & 1)) / 2), col(u) {
    if (u + v + w != 0) {
        throw std::invalid_argument("u + v + w must be 0");
    }
}

HexPos::HexPos(int u, int v)
    : HexPos(u, v, -u-v) {}

int HexPos::distance(const HexPos& b) const {
    return (std::abs(u - b.u) + std::abs(v - b.v) + std::abs(w - b.w)) / 2;
}

bool HexPos::is_neighbor(const HexPos& b) const {
    return distance(b) == 1;
}

std::vector<HexPos> HexPos::neighbors() const {
    return {
        HexPos(u + 1, v - 1), HexPos(u + 1, v), HexPos(u, v + 1),
        HexPos(u - 1, v + 1), HexPos(u - 1, v), HexPos(u, v - 1)
    };
}

std::string HexPos::str() const {
    std::stringstream ss;
    ss << std::string(1, (row +'a')) << col;
    return ss.str();
}


GameHex::GameHex(int u, int v, gold_t production, player_id_t owner)
    : pos(HexPos(u, v)), production(production), owner(owner){ }