#include <iostream>

#include "game.h"

int main(int argc, char* argv[])
{
    bool isDebug = false;
    if(argc == 2)
    {
        isDebug = (std::string("debug") == std::string(argv[1]));
        std::cout << "running in debug mode" << std::endl;
    }
    
    Game NewGame(isDebug);
    if(NewGame.startGame() != GAME_CLOSED_NORMALLY)
    {
        std::cout << "game had an unknown error. suddenly closed.";
    }

    return 0;
}
