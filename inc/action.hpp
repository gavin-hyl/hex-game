#pragma once

struct Action {
    enum TYPE {
        ANNEX,
        ATTACK,
        DEFEND,
        RESEARCH,
        END_TURN
    };

    TYPE type;
    int cost;
};

