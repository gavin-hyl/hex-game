#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <set>

#include "hex.hpp"
#include "colors.hpp"

struct Board {
    Board(int size = 0);
    GameHex* get_hex(const HexPos& pos);
    std::vector<GameHex*> get_ring(HexPos center, int radius);
    const bool in_bounds(const HexPos& pos) const;
    
    int size;
    std::vector<GameHex> hexes;
};