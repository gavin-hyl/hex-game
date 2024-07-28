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
#include "action.hpp"
#include "graphs.hpp"


class Game {
    public:
        Game(int size, int players = 2);
        bool next_turn();
        void print();

    private:
        Board board = Board();
        Canvas canvas = Canvas();
        std::vector<Player> players;
        GameHex* selected_hex = nullptr;
        player_id_t current_id = 0;
        int turn = 0;

        const static gold_t BASE_PROD = 1;

        const static player_id_t NO_PLAYER = -1;
        const static gold_t win_gold = 30;
        const static std::vector<double> prod_distribution;
        const static std::vector<gold_t> prod_values;
        const static std::vector<HexPos> capitals_rel;
        std::vector<HexPos> capitals;

        Randomizer rng = Randomizer();

        const std::map<std::string, PlayerAction> actions = {
            {
                "annex", 
                PlayerAction(ActionCost(3, 0, 0),
                            "Gain control of a hex.",
                            [this](){return this->check_annex();},
                            [this](){this->annex();})
            },
            {
                "shield", 
                PlayerAction(ActionCost(5, 0, 0),
                            "Add a" + SHIELD_STR + "to a hex",
                            [this](){return this->check_add_shield();},
                            [this](){this->add_shield();})
            },
            {
                "sword", 
                PlayerAction(ActionCost(5, 0, 0),
                            "Add a " + SWORD_STR + " to a hex",
                            [this](){return this->check_add_sword();},
                            [this](){this->add_sword();})
            },
            {
                "attack", 
                PlayerAction(ActionCost(0, 1, 0),
                            "Attack a hex with a "+SWORD_STR+". If the hex is owned by another player,"
                            "reduce its " +  SHIELD_STR + " count by 1. If the " + SHIELD_STR + " is 0,"
                            "that hex is neutralized.",
                            [this](){return this->check_attack();},
                            [this](){this->attack();})
            },
            {
                "improve", 
                PlayerAction(ActionCost(0, 1, 1),
                            "Increase " + GOLD_STR + " of a hex by 1.",
                            [this](){return this->check_improve();},
                            [this](){this->improve();})
            }
        };

        bool check_annex();
        void annex();
        bool check_add_shield();
        void add_shield();
        bool check_add_sword();
        void add_sword();
        bool check_attack();
        void attack();
        bool check_improve();
        void improve();

        bool affordable(const ActionCost& cost) const;
        void incur(const ActionCost& cost);

        // bool research(Tech& tech);

        // const ACTION parse_action() const;
        const Tech& get_tech() const;
        GameHex& get_hex(std::string coords="");

        Player& current_player() const;
        gold_t player_prodution(player_id_t id) const;

        bool accessible(const GameHex& hex, int dist=1) const;
};
