#include "tech.hpp"

Tech EndGame("End Tech", "You win", 0, {});
Tech EconT2("Currency", "All tiles +1 gold", 10, {&EndGame});
Tech EconT1("Metal Tools", "Production tiles +1 ", 10, {&EconT2});
Tech EconT0("Organization", "Production tiles +1 ", 20, {&EconT1});
Tech AttackT2("Firearms", "Attack twice", 10, {&EndGame});
Tech AttackT1("Conscription", "Attack cost -1", 10, {&AttackT2});
Tech AttackT0("Standing Army", "Attack cost -1", 20, {&AttackT1});
Tech DefenseT2("Civil Service", "All tiles produce +1 defender every 2 turns (max 3)", 10, {&EndGame});
Tech DefenseT1("Castles", "All tiles +1 defender", 10, {&DefenseT2});
Tech DefenseT0("Shields", "All tiles +1 defender", 20, {&DefenseT1});
Tech Base("Civilization", "You started here", 0, {&EconT0, &AttackT0, &DefenseT0});

#define MAP_ENTRY(x) {x.name, x}

std::map<std::string, Tech> techs = {
    MAP_ENTRY(EndGame),
    MAP_ENTRY(EconT2),
    MAP_ENTRY(EconT1),
    MAP_ENTRY(EconT0),
    MAP_ENTRY(AttackT2),
    MAP_ENTRY(AttackT1),
    MAP_ENTRY(AttackT0),
    MAP_ENTRY(DefenseT2),
    MAP_ENTRY(DefenseT1),
    MAP_ENTRY(DefenseT0),
    MAP_ENTRY(Base)
};