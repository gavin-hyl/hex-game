#include "game.hpp"

#include <iostream>

int main(int argc, char const *argv[])
{
    Game game(5, 2);
    game.print();
    while (1)
    {
        game.next_turn();
        game.print();
    }
}
