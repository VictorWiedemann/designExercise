#include "game.h"

#include <iostream>
#include <stdlib.h>

Game::Game()
{
    std::cout << "hello world" << std::endl;
    for (int i = 1; i <= NUM_OF_LEDS; i++)
    {
        // off by one because we want to label the leds 1-3, but store them 0-2
        Leds[i - 1] = new Led(i);
    }

    InputButtons = new Buttons;
}

Game::~Game()
{
    for (Led *eachLed : Leds)
    {
        delete eachLed;
    }

    delete InputButtons;
}

uint8_t Game::startGame()
{
    gameState currentState = GAME_START;
    try
    {
        // full restart
        while (currentState != GAME_EXIT)
        {
            dealWithCurrentState(currentState);
        }
    }
    catch (int error)
    {
        return GAME_UNEXPECTED_ERROR;
    }

    return GAME_CLOSED_NORMALLY;
}

gameState Game::dealWithCurrentState(gameState currentState)
{
    switch (currentState)
    {

    case GAME_START:
    {
        generateNewSequence();
        return GAME_RUNNING;
    }
    case GAME_RUNNING:
    {
        for (int i = 0; i < NUM_OF_LEDS; i++)
        {
            buttonPressed buttonRecv = InputButtons->getButtonInput();
            if((buttonRecv < BUTTON_A) || (buttonRecv > BUTTON_C))
            {
                std::cout << "DEV ERROR, button that was recieved is out of range... quitting game\n";
                return GAME_EXIT;
            }
            
            gameState newState = checkGuess(buttonRecv);

            setLedsStates();
            setLedsStates();
        }
    }
    case GAME_RETRY:
    {
        std::cout << "game failure press any button to reset\n This will be removed";
        InputButtons->getButtonInput();
        restartGuesses();
        setLedsStates();
    }
    case GAME_WIN:
    {
        //QUESTION: The requirements say to restart right away after a win. I would recommend letting players
        //enjoy their win before resetting it immediately.
        restartGuesses();
        setLedsStates();
    }
    default:
        return GAME_EXIT;
    }
}

void Game::restartGuesses()
{
    for (int i = 0; i < NUM_OF_LEDS; i++)
    {
        guesses[i] = BUTTON_NOT_PRESSED;
    }
}

void Game::generateNewSequence()
{
    srand(time(NULL));
    for (int i = 0; i < NUM_OF_LEDS; i++)
    {
        sequence[i] = (buttonPressed)(rand() % NUM_OF_PLAYABLE_BUTTONS);
    }

    sequence[0] = BUTTON_A;
    sequence[1] = BUTTON_B;
    sequence[2] = BUTTON_C;
}

gameState Game::checkGuess(buttonPressed buttonRecv)
{
    //TODO VICTOR check the guess logic.
    return GAME_RUNNING;
}

void Game::setLedsStates()
{
    //TODO VICTOR setup the new LED states here based on the guesses
    refreshScreen(); // TODO delete this line when we switch to hardware
}

//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
// TODO delete everything below this comment when switching to hardware
#include <ncurses.h>
#include <stdlib.h>

void Game::refreshScreen()
{
    system("clear");
    std::cout << "   LED 1       LED 2       LED 3" << std::endl;
    for (Led *eachLed : Leds)
    {
        std::string ledString = getColourText(eachLed->getLedColour());
        std::cout << "   " << ledString << "   ";
    }
    std::cout << std::endl;
}

std::string Game::getColourText(ledColour colour)
{
    switch (colour)
    {
    case LED_GREEN:
        return "GREEN ";
    case LED_RED:
        return "RED   ";
    case LED_ORANGE:
        return "ORANGE";
    case LED_OFF:
        return "OFF   ";
    default:
        return "ERROR ";
    }
}
