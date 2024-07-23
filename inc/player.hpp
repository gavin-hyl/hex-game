#pragma once

#include <vector>
#include <set>

#include "tech.hpp"
#include "hex.hpp"

struct Player {
    int gold;
    std::set<Tech*> researched_techs;
    std::set<Tech*> potential_techs;
    std::set<GameHex*> owned_hexes;

    Player() : gold(0) {}

    bool researched(Tech& tech) {
        return (researched_techs.find(&tech) != researched_techs.end());
    }
};