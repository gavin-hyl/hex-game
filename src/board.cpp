#include "board.hpp"

Board::Board(std::vector<GameHex> hexes) {
    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int col = 0; col < GRID_WIDTH; col++) {
            Board::grid[row][col] = ' ';
            Board::grid_colors[row][col] = RESET;
        }
    }
    for (auto hex : hexes) {
        std::stringstream pos, prod, atk, def;
        pos << "(" << std::string(1, (hex.u +'a')) << hex.v << ")";
        prod << "  +" << hex.production;
        atk << "A" << hex.attackers;
        def << "D" << hex.defenders;
        place_hexagon(hex.row, hex.col, {pos.str(), prod.str(), atk.str(), def.str(), ""}, {GRAY, GREEN, RED, BLUE});
    }
}

void Board::print_bound_line() {
    std::cout << "+";
    for (int col = 0; col < GRID_WIDTH; col++) {
        std::cout << "-";
    }
    std::cout << "+\n";
}

void Board::place_hexagon(int row, int col, const std::vector<std::string>& text, 
const std::vector<std::string>& colors) {
    int grid_start_col = col * HEX_WIDTH_OFFSET;
    int grid_start_row = row * HEX_HEIGHT_OFFSET;
    if (col & 1) {
        grid_start_row += HEX_HEIGHT_OFFSET / 2;
    }
    unsigned int txt_cnt = 0;
    for (unsigned int hrow = 0; hrow < HEXAGON.size(); hrow++) {
        for (unsigned int hcol = 0; hcol < HEXAGON[hrow].size(); hcol++) {
            int grid_row = grid_start_row + hrow;
            int grid_col = grid_start_col + hcol;
            char hex_char = HEXAGON[hrow][hcol];
            char& grid_char = grid[grid_start_row + hrow][grid_start_col + hcol];
            std::string& grid_color = grid_colors[grid_start_row + hrow][grid_start_col + hcol];
            if (grid_row < 0 || grid_row >= GRID_HEIGHT     // check bounds
                || grid_col < 0 || grid_col >= GRID_WIDTH
                || hex_char == ' ') {     // don't overwrite
                continue;
            }
            if ((hex_char >= '0') && (hex_char <= '9')) {
                unsigned int index = hex_char - '0';
                std::cerr << index << std::endl;
                const std::string& txt = text.at(index);
                if (txt_cnt < txt.size()) {
                    grid_char = txt.at(txt_cnt);
                    grid_color = colors.at(index);
                    txt_cnt++;
                } else {
                    grid_char = ' ';
                    grid_color = RESET;
                    txt_cnt = 0;
                }
            } else {
                grid_char = hex_char;
                grid_color = RESET;
                // txt_cnt = 0;
            }
        }
    }
}

void Board::print() const{
    Board::print_bound_line();
    for (int row = 0; row < Board::GRID_HEIGHT; row++) {
        std::cout << "|";
        for (int col = 0; col < Board::GRID_WIDTH; col++) {
            char c = this->grid[row][col];
            if (GRID_CHARS.find(c) != GRID_CHARS.end()) {
                std::cout << GRAY << c << RESET;
            } else {
                std::cout << this->grid_colors[row][col] << c;
            }
        }
        std::cout << "|\n";
    }
    Board::print_bound_line();
}