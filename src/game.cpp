#include "game.h"

#include <iostream>
#include <stdlib.h>

Game::Game(bool isDebug)
{
    debugMode = isDebug;
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
        // will exit out if any game breaking issue is hit.
        while (currentState != GAME_EXIT)
        {
            currentState = dealWithCurrentState(currentState);
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
        if (debugMode)
        {
            std::cout << "Starting new game" << std::endl;
        }
        generateNewSequence();
        restartGuesses();
        setLedsStates();
        return GAME_RUNNING;
    }
    case GAME_RUNNING:
    {
        if (debugMode)
        {
            std::cout << "restarted the guesses" << std::endl;
        }
        for (int i = 0; i < NUM_OF_LEDS; i++)
        {
            buttonPressed buttonRecv = InputButtons->getButtonInput();
            if ((buttonRecv < BUTTON_A) || (buttonRecv > BUTTON_C))
            {
                std::cout << "the pressed was out of range... quitting game\n"
                          << std::endl;
                return GAME_EXIT;
            }

            gameState newState = checkGuess(buttonRecv, i);

            setLedsStates();
            // catch any exit conditions.
            if (newState != GAME_RUNNING)
            {
                return newState;
            }
        }
    }
    case GAME_RETRY:
    {
        restartGuesses();
        return GAME_RUNNING;
    }
    case GAME_WIN:
    {
        // QUESTION: The requirements say to restart right away after a win. I would recommend letting players
        // enjoy their win before resetting it immediately. I will program with my recommendation.
        return GAME_START;
    }
    default:
        std::cout << "enexpected error, exiting now." << std::endl;
        return GAME_EXIT;
    }
}

void Game::restartGuesses()
{
    for (int i = 0; i < NUM_OF_LEDS; i++)
    {
        userGuesses[i] = GUESS_EMPTY;
    }
}

void Game::generateNewSequence()
{
    srand(time(NULL));
    for (int i = 0; i < NUM_OF_LEDS; i++)
    {
        sequence[i] = (buttonPressed)(rand() % NUM_OF_PLAYABLE_BUTTONS);
    }
}

gameState Game::checkGuess(buttonPressed buttonRecv, int guessLocation)
{
    // TODO VICTOR check the guess logic.
    if ((guessLocation < 0) || guessLocation >= NUM_OF_LEDS)
    {
        std::cout << "guess number is out of range. Dev error" << std::endl;
        return GAME_EXIT;
    }

    // We are directly attaching the guess correctness to the LED state. I would decouple these if there was
    // any different logic to the game requirements.
    if ((int)buttonRecv == (int)sequence[guessLocation])
    {
        userGuesses[guessLocation] = GUESS_CORRECT;
    }
    else if (isInSequence(buttonRecv))
    {
        userGuesses[guessLocation] = GUESS_DIFF_SPOT;
    }
    else
    {
        userGuesses[guessLocation] = GUESS_WRONG;
    }

    // if last guess
    if (guessLocation == NUM_OF_LEDS - 1)
    {
        return setGameEndState();
    }

    // QUESTION:: if a player was to guess CBB and the seqeunce was BAA, would the two Bs both be orange? Or would only one?
    // ASSUMPTION: I will assume that both Bs in the above case is orange, but I would want to confirm this first.
    return GAME_RUNNING;
}

void Game::setLedsStates()
{
    // from the last LED to the first. See requirements for details.
    for (int i = NUM_OF_LEDS - 1; i >= 0; i--)
    {
        if (userGuesses[i] == GUESS_CORRECT)
        {
            Leds[i]->setLedColour(LED_GREEN);
        }
        else if (userGuesses[i] == GUESS_DIFF_SPOT)
        {
            Leds[i]->setLedColour(LED_ORANGE);
        }
        else if (userGuesses[i] == GUESS_WRONG)
        {
            Leds[i]->setLedColour(LED_RED);
        }
        else
        {
            Leds[i]->setLedColour(LED_OFF);
        }
    }
    refreshScreen(); // TODO delete this line when we switch to hardware
}

bool Game::isInSequence(buttonPressed buttonRecv)
{
    for (buttonPressed partOfSequence : sequence)
    {
        if ((int)buttonRecv == (int)partOfSequence)
        {
            return true;
        }
    }
    return false;
}

// ASSUMPTION: since the L
gameState Game::setGameEndState()
{
    for (guesses userGuess : userGuesses)
    {
        if (userGuess != GUESS_CORRECT)
        {
            return GAME_RETRY;
        }
    }
    return GAME_WIN;
}

//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
// TODO delete everything below this comment when switching to hardware
#include <stdlib.h>

void Game::refreshScreen()
{
    system("clear");

    if (debugMode)
    {
        printDebugInfo();
    }

    std::cout << "   LED 1       LED 2       LED 3" << std::endl;
    for (Led *eachLed : Leds)
    {
        std::string ledString = getColourText(eachLed->getLedColour());
        std::cout << "   " << ledString << "   ";
    }
    std::cout << std::endl;
}

void Game::printDebugInfo()
{
    std::cout << "pattern is: ";
    for (int i = 0; i < NUM_OF_LEDS; i++)
    {
        switch (sequence[i])
        {
        case BUTTON_A:
            std::cout << " A ";
            break;
        case BUTTON_B:
            std::cout << " B ";
            break;
        case BUTTON_C:
            std::cout << " C ";
            break;
        default:
            std::cout << " error, bad sequence value ";
        }
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
