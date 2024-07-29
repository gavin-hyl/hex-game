#include "action.hpp"

const std::string ActionCost::to_string() const {
    return COLOR(YELLOW, std::string(gold, '+'))
            + COLOR(RED, std::string(swords, 'x'))
            + COLOR(BLUE, std::string(shields, 'o'));
}