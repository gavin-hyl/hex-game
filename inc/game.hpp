#pragma once

#include <vector>
#include <set>
#include <random>

#include "hex.hpp"
#include "player.hpp"
#include "rng.hpp"
#include "ui.hpp"
#include "tech.hpp"
#include "board.hpp"

struct PlayerAction {
    int cost;
    std::function<bool()> act_fn;
    std::string cost_description;
    std::string description;
};

class Game {
    public:
        Game(int size, int players = 2);
        bool next_turn();
        void print();

    private:
        Board board = Board();
        std::vector<Player> players;
        const int NO_PLAYER = -1;
        int current_player_idx = 0; 
        int win_gold = 30;
        int turn = 0;
        bool ended = false;
        const static std::vector<double> prod_distribution;
        const static std::vector<int> prod_values;
        Randomizer rng = Randomizer();

        static const std::string ANNEX;
        static const std::string ATTACK;
        static const std::string SWORD;
        static const std::string SHIELD;
        static const std::string IMPROVE;
        static const std::string TAKEOVER;
        static const std::vector<std::string> action_strings;

        const std::map<std::string, PlayerAction> actions = {
            {ANNEX, PlayerAction(5, [this](){return this->annex();}, COLOR(YELLOW, "5G"), "Annex a hex")},
            {TAKEOVER, PlayerAction(5, [this](){return this->annex();}, COLOR(RED, "xx"), "Take over a hex")},
            {SWORD, PlayerAction(5, [this](){return this->add_sword();}, COLOR(YELLOW, "5G"), "Add a sword to a hex")},
            {SHIELD, PlayerAction(5, [this](){return this->add_shield();}, COLOR(YELLOW, "5G"), "Add a shield to a hex")},
            {ATTACK, PlayerAction(0, [this](){return this->attack();}, COLOR(RED, "x"), "Attack a hex")},
            {IMPROVE, PlayerAction(0, [this](){return this->improve();}, COLOR(BLUE, "oo"), "Increase production of a hex by 1")},
        };


        bool annex();
        bool takeover();
        bool add_shield();
        bool add_sword();
        bool attack();
        bool improve();

        // bool research(Tech& tech);

        // const ACTION parse_action() const;
        const Tech& get_tech() const;
        GameHex& get_hex();

        Player& current_player() const;
        const void next_player();

        bool accessible(const GameHex& hex, int dist=1) const;
};
