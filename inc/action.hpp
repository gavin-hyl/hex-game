#pragma once

#include <string>
#include <functional>

#include "colors.hpp"

using gold_t = unsigned int;
using sword_t = unsigned int;
using shield_t = unsigned int;

struct ActionCost {
    gold_t gold;
    sword_t swords;
    shield_t shields;

    ActionCost(gold_t gold, sword_t swords, shield_t shields) 
        : gold(gold), swords(swords), shields(shields) {}
    
    std::string to_string() const {
        return COLOR(YELLOW, std::string(gold, '+'))
                + COLOR(RED, std::string(swords, 'x'))
                + COLOR(BLUE, std::string(shields, 'o'));
    }
};

struct PlayerAction {
    ActionCost cost;
    std::string description;
    std::function<bool()> check;
    std::function<void()> act;
};