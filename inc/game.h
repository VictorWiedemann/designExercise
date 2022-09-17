#pragma once

#include <stdint.h>
#include <string>

#include "led.h"
#include "buttons.h"

enum
{
    GAME_CLOSED_NORMALLY = 0,
    GAME_UNEXPECTED_ERROR,
};

typedef enum gameState
{
    GAME_START,
    GAME_RUNNING,
    GAME_INCORRECT,
    GAME_RETRY,
    GAME_RESTART,
}gameState;

class Game
{

public:
    Game();
    ~Game();

    /**
     * @brief Blocking call to get the latest button Input
     * //TODO make this input be non-blocking later in a production setting. Maybe a timeout in a loop to check for ctrl+c
     */
    uint8_t startGame();

private:

    Led* Leds[NUM_OF_LEDS];
    Buttons *inputButtons;

    /**
     * @brief Shows the state of the game on a terminal
     *   TODO remove this function. This just displays the current state of the leds.
     *   led.h will handle showing the state of the leds.
     * 
     */
    void refreshScreen();

    /**
     * @brief Get the Text for the supplied color
     * TODO remove this function when we move to real hardware.
     * This is just used for visualiazation on the terminal
     * 
     * @param colour the enum from led.h
     * @return string to print to the screeen
     */
    std::string getColourText(ledColour colour);
};