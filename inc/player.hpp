#pragma once

#include <vector>
#include <set>
#include <iostream>

#include "tech.hpp"
#include "action.hpp"

using player_id_t = char;

struct Player {
    gold_t gold;
    std::set<Tech*> researched_techs;
    std::set<Tech*> potential_techs;

    Player() : gold(0) {
        researched_techs.insert(&Base);
    }

    bool researched(Tech& tech) {
        return (researched_techs.find(&tech) != researched_techs.end());
    }

    friend std::ostream &operator<<(std::ostream &os, const Player &player) {
        // os << "Player(gold=" << player.gold << ", researched_techs=[";
        // for (const auto& tech : player.researched_techs) {
        //     os << tech->name << ", ";
        // }
        // os << "], potential_techs=[";
        // for (const auto& tech : player.potential_techs) {
        //     os << tech->name << ", ";
        // }
        // os << "])";
        // return os;
        os << "Player [" << player.gold << "G]";
        return os;
    }
};