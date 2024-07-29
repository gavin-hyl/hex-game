#include "game.hpp"

#include <iostream>

int main()
{
    Game game(3, 2);
    game.print();
    while (1)
    {
        game.next_turn();
    }
}
