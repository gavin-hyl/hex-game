#include "board.hpp"

Board::Board(std::vector<GameHex> hexes) {
    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int col = 0; col < GRID_WIDTH; col++) {
            Board::grid[row][col] = ' ';
            Board::grid_colors[row][col] = RESET;
        }
    }
    update_hexes(hexes);
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
    
    unsigned int txt_char_idx = 0;
    unsigned int curr_idx = 0;

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

void Board::place_game_hex(const GameHex &hex)
{
    std::stringstream pos;
    pos << std::string(1, (hex.u +'a')) << "-" << hex.v;
    std::string prod = std::string(hex.production, '+');
    std::string atk = std::string(hex.swords, 'x');
    std::string def = std::string(hex.shields, 'o');
    std::string pos_color = (hex.owner != -1) ? PLAYER_COLORS.at(hex.owner) : GRAY;
    std::string prod_color = hex.owner == -1 ? WHITE : PLAYER_COLORS.at(hex.owner);
    place_hexagon(hex.row, hex.col, {pos.str(), prod, atk, def}, {pos_color, prod_color, RED, BLUE});
}

void Board::print() const{
    Board::print_bound_line();
    for (int row = 0; row < Board::GRID_HEIGHT; row++) {
        std::cout << "|";
        for (int col = 0; col < Board::GRID_WIDTH; col++) {
            char c = this->grid[row][col];
            if (GRID_CHARS.find(c) != GRID_CHARS.end()) {
                std::cout << GRAY << c;
            } else {
                std::cout << this->grid_colors[row][col] << c;
            }
        }
        std::cout << "|\n";
    }
    Board::print_bound_line();
}

void Board::update_hexes(const std::vector<GameHex> &hexes)
{
    for (auto& hex : hexes) {
        place_game_hex(hex);
    }
}
