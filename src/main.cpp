#include <iostream>

#include "game.h"

//TODO remove ncurses when we move to new hardware
#include <ncurses.h>

int main(int argc, char* argv[])
{
    Game NewGame;
    
    if(NewGame.startGame() != GAME_CLOSED_NORMALLY)
    {
        std::cout << "game had an unknown error. suddenly closed.";
    }

    return 0;
}
