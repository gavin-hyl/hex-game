#pragma once

#include <iostream>
#include <unordered_set>

#include "colors.hpp"
#include "hex.hpp"

std::string get_input(std::string prompt);

void wait();

void clear_terminal();

class Canvas {
public:
    Canvas(bool compact = true);
    void print();

    // canvas is a 2D array of characters that represents the game board
    const static int CANVAS_HEIGHT = 60;
    const static int CANVAS_WIDTH = 120;
    char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    color_t canvas_colors[CANVAS_HEIGHT][CANVAS_WIDTH];

    // settings for hexagon placement
    const static int HEX_HEIGHT_COMPACT = 4;
    const static int HEX_WIDTH_COMPACT = 8;
    const static int HEX_HEIGHT_SPACED = 5;
    const static int HEX_WIDTH_SPACED = 10;
    size_t hex_width, hex_height;
    
    void print_bound_line();

    void reset();
    void update(const std::vector<GameHex>& hexes);
    void place_game_hex(const GameHex& hex);
    void place_hexagon(int row, int col,
                        const std::vector<std::string>& text, 
                        const std::vector<color_t>& colors);
};

const static std::vector<std::string> HEXAGON = {
    "  ______  ",
    " / 0000 \\ ",
    "/ 111111 \\",
    "\\ 222333 /",
    " \\______/ "
};

const static std::unordered_set<char> GRID_CHARS = {'\\', '_', '/'};