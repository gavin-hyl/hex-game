#include "board.hpp"

Board::Board(int size, bool compact)
    : size(size) {
    hex_width = compact ? HEX_WIDTH_COMPACT : HEX_WIDTH_SPACED;
    hex_height = compact ? HEX_HEIGHT_COMPACT : HEX_HEIGHT_SPACED;
    reset_canvas();
    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            if (!in_bounds(HexPos(i, j))) {
                continue;
            }
            hexes.emplace_back(GameHex(i+size, j+size));
        }
    }
}

void Board::print_bound_line() {
    std::cout << "+";
    for (int col = 0; col < CANVAS_WIDTH; col++) {
        std::cout << "-";
    }
    std::cout << "+\n";
}

void Board::reset_canvas() {
    for (int row = 0; row < CANVAS_HEIGHT; row++) {
        for (int col = 0; col < CANVAS_WIDTH; col++) {
            canvas[row][col] = ' ';
            canvas_colors[row][col] = RESET;
        }
    }
}

void Board::update_canvas() {
    reset_canvas();
    for (const GameHex& hex : hexes) {
        place_game_hex(hex);
    }
}

void Board::place_hexagon(int row, int col,
                          const std::vector<std::string>& text, 
                          const std::vector<std::string>& colors) {
    int grid_start_col = col * hex_width;
    int grid_start_row = row * hex_height;
    if (col & 1) {
        grid_start_row += hex_height / 2;
    }
    
    unsigned int txt_char_idx = 0;
    unsigned int curr_idx = 0;

    for (unsigned int hrow = 0; hrow < HEXAGON.size(); hrow++) {
        for (unsigned int hcol = 0; hcol < HEXAGON[hrow].size(); hcol++) {
            int grid_row = grid_start_row + hrow;
            int grid_col = grid_start_col + hcol;
            char hex_char = HEXAGON[hrow][hcol];
            char& grid_char = canvas[grid_start_row + hrow][grid_start_col + hcol];
            std::string& grid_color = canvas_colors[grid_start_row + hrow][grid_start_col + hcol];
            if (grid_row < 0 || grid_row >= CANVAS_HEIGHT     // check bounds
                || grid_col < 0 || grid_col >= CANVAS_WIDTH
                || hex_char == ' ') {     // don't overwrite
                continue;
            }
            if ((hex_char >= '0') && (hex_char <= '9')) {
                // substitute hex_char if it's a digit
                unsigned int index = hex_char - '0';
                // reset text if we're on a new index
                if (curr_idx != index) {
                    txt_char_idx = 0;
                    curr_idx = index;
                }
                const std::string& txt = text.at(curr_idx);
                if (txt_char_idx < txt.size()) {
                    grid_char = txt.at(txt_char_idx);
                    grid_color = colors.at(curr_idx);
                    txt_char_idx++;
                } else {
                    grid_char = ' ';
                    grid_color = RESET;
                }
            } else {
                grid_char = hex_char;
                grid_color = RESET;
                txt_char_idx = 0;
            }
        }
    }
}

bool Board::in_bounds(const HexPos &pos) const
{
    return (abs(pos.u + pos.v) <= size);
}

GameHex &Board::get_hex(const HexPos &pos)
{
    for (GameHex &hex : hexes) {
        if (hex.pos == pos) {
            return hex;
        }
    }
    throw std::invalid_argument("Invalid hex coords.");
}

// std::vector<GameHex&> Board::get_ring(HexPos center, int radius)
// {
    // if (radius < 0) {
    //     throw std::invalid_argument("Radius must be non-negative.");
    // }
    // std::vector<GameHex &> ring;
    // if (radius == 0) {
    //     ring.emplace_back(get_hex(center));
    // } else {
    //     for (const GameHex& hex : hexes) {
    //         if (center.distance(hex.pos) == radius) {
    //             ring.emplace_back(hex);
    //         }
    //     }
    // }
    // return ring;
// }

void Board::place_game_hex(const GameHex &hex)
{
    std::stringstream pos;
    pos << std::string(1, (hex.pos.u +'a')) << "-" << hex.pos.v;
    std::string prod = std::string(hex.production, '+');
    std::string atk = std::string(hex.swords, 'x');
    std::string def = std::string(hex.shields, 'o');
    std::string pos_color = GRAY;
    std::string prod_color = GRAY;
    if (hex.owner != -1) {
        pos_color = PLAYER_COLORS.at(hex.owner);
        prod_color = YELLOW;
    }
    place_hexagon(hex.pos.row, hex.pos.col, {pos.str(), prod, atk, def}, {pos_color, prod_color, RED, BLUE});
}

void Board::print() {
    print_bound_line();
    update_canvas();
    for (int row = 0; row < Board::CANVAS_HEIGHT; row++) {
        std::cout << "|";
        for (int col = 0; col < Board::CANVAS_WIDTH; col++) {
            char c = this->canvas[row][col];
            color_t color = (GRID_CHARS.find(c) != GRID_CHARS.end()) ? GRAY : this->canvas_colors[row][col];
            std::cout << color << c;
        }
        std::cout << RESET << "|\n";
    }
    print_bound_line();
}