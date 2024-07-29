#pragma once

#include <string>
#include <functional>

#include "colors.hpp"
#include "types.hpp"

struct ActionCost {
    gold_t gold;
    sword_t swords;
    shield_t shields;

    const std::string to_string() const;
};


struct PlayerAction {
    ActionCost cost;
    std::string description;
    std::function<bool()> check;
    std::function<void()> act;
};