#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <set>

#include "hex.hpp"
#include "colors.hpp"

class Board {
    public:
        Board() = default;
        Board(int size, bool compact = true);
        std::vector<GameHex> hexes;
        GameHex* get_hex(const HexPos& pos);
        std::vector<GameHex*> get_ring(HexPos center, int radius);

    private:
        int size;
        bool in_bounds(const HexPos& pos) const;
};