#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

struct Tech {
    const std::string name;
    const std::string description;
    const int cost;
    const std::vector<Tech*> children;

    Tech(std::string name, std::string description, int cost, std::initializer_list<Tech*> children)
        : name(name), description(description), cost(cost), children(children) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Tech& tech) {
        os << tech.name << " - " << tech.description << " - " << tech.cost;
        return os;
    }
};

extern Tech EndGame;
extern Tech EconT2;
extern Tech EconT1;
extern Tech EconT0;
extern Tech AttackT2;
extern Tech AttackT1;
extern Tech AttackT0;
extern Tech DefenseT2;
extern Tech DefenseT1;
extern Tech DefenseT0;
extern Tech Base;
extern std::map<std::string, Tech> techs;