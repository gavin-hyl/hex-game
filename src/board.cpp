#include "board.hpp"

Board::Board(int size, bool compact)
    : size(size) {
    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            if (!in_bounds(HexPos(i, j))) {
                continue;
            }
            hexes.emplace_back(GameHex(i+size, j+size));
        }
    }
}

bool Board::in_bounds(const HexPos &pos) const
{
    return (abs(pos.u + pos.v) <= size);
}

GameHex* Board::get_hex(const HexPos &pos)
{
    for (GameHex &hex : hexes) {
        if (hex.pos == pos) {
            return &hex;
        }
    }
    throw std::invalid_argument("Invalid hex coords.");
}


std::vector<GameHex*> Board::get_ring(HexPos center, int radius)
{
    if (radius < 0) {
        throw std::invalid_argument("Radius must be non-negative.");
    }
    std::vector<GameHex*> ring;
    if (radius == 0) {
        ring.emplace_back(get_hex(center));
    } else {
        for (GameHex& hex : hexes) {
            if (center.distance(hex.pos) == radius) {
                ring.emplace_back(&hex);
            }
        }
    }
    return ring;
}