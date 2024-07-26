#pragma once

#include <string>

#include "game.hpp"

struct Action {
    Action(Game& game, std::string name, std::string cost_description, std::string description)
        : game(game), name(name), cost_description(cost_description), description(description) {}
    Game& game;
    virtual bool check() = 0;
    virtual bool act() = 0;
    virtual bool cost() = 0;
    std::string name;
    std::string cost_description;
    std::string description;
};


struct Annex : public Action {
    Annex(Game& game) : Action(game, "Annex", "5G", "Annex a hex") {}
    bool check() override {
        return true;
    }
    bool act() override {
        return game.annex();
    }
    bool cost() override {
        return game.current_player().gold >= 5;
    }
};