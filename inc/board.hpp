#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <set>

#include "hex.hpp"
#include "colors.hpp"

struct Board {
    const static int GRID_WIDTH = 120;
    const static int GRID_HEIGHT = 60;
    const static int HEX_HEIGHT_OFFSET = 4;
    const static int HEX_WIDTH_OFFSET = 8;
    char grid[GRID_HEIGHT][GRID_WIDTH];
    std::string grid_colors[GRID_HEIGHT][GRID_WIDTH];

    Board(std::vector<GameHex> hexes);
    Board() = default;
    void print() const;
    void update_hexes(const std::vector<GameHex>& hexes);

    private:
    static void print_bound_line();
    void place_hexagon(int row, int col, const std::vector<std::string>& text,
                       const std::vector<std::string>& colors);
    void place_game_hex(const GameHex& hex);
};

const static std::vector<std::string> HEXAGON = {
    "  ______  ",
    " / 0000 \\ ",
    "/ 111111 \\",
    "\\ 222333 /",
    " \\______/ "
};

const static std::set<char> GRID_CHARS = {'\\', '_', '/'};