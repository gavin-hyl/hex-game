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
        Board(std::vector<GameHex> hexes = {}, bool compact = true);
        void print();
        std::vector<GameHex> hexes;

    private:
        // canvas is a 2D array of characters that represents the game board
        const static int CANVAS_HEIGHT = 60;
        const static int CANVAS_WIDTH = 150;
        char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
        color_t canvas_colors[CANVAS_HEIGHT][CANVAS_WIDTH];

        // settings for hexagon placement
        const static int HEX_HEIGHT_COMPACT = 4;
        const static int HEX_WIDTH_COMPACT = 8;
        const static int HEX_HEIGHT_SPACED = 5;
        const static int HEX_WIDTH_SPACED = 10;
        size_t hex_width, hex_height;
        
        void print_bound_line();

        void reset_canvas();
        void update_canvas();
        void place_game_hex(const GameHex& hex);
        void place_hexagon(int row, int col,
                           const std::vector<std::string>& text, 
                           const std::vector<color_t>& colors);

        GameHex& get_hex(const HexPos& pos);
        bool is_fair(const std::vector<HexPos>& capitals);
};

const static std::vector<std::string> HEXAGON = {
    "  ______  ",
    " / 0000 \\ ",
    "/ 111111 \\",
    "\\ 222333 /",
    " \\______/ "
};

const static std::set<char> GRID_CHARS = {'\\', '_', '/'};