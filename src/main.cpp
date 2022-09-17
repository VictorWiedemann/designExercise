#include <iostream>

#include "game.h"

int main(int argc, char* argv[])
{
    Game NewGame;
    
    if(NewGame.startGame() != GAME_CLOSED_NORMALLY)
    {
        std::cout << "game had an unknown error. suddenly closed.";
    }

    return 0;
}
