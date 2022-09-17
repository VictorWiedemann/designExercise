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
    GAME_RETRY,
    GAME_WIN,
    GAME_EXIT,
} gameState;

class Game
{

public:
    Game();
    ~Game();

    /**
     * @brief the main loop of the game
     * 
     * @return uint8_t an error code
     */
    uint8_t startGame();

private:
    Led *Leds[NUM_OF_LEDS];
    Buttons *InputButtons;
    buttonPressed sequence[NUM_OF_LEDS];
    buttonPressed guesses[NUM_OF_LEDS];

    /**
     * @brief restarts the guesses of the game
     *
     */
    void restartGuesses();

    /**
     * @brief Get the New sequence to play the game with
     *
     */
    void generateNewSequence();

    /**
     * @brief hecks the supplied guess by the player. Can change the state of the game.

     * 
     * @param buttonRecv the button that has been pressed most recently
     */
    gameState checkGuess(buttonPressed buttonRecv);

    /**
     * @brief The controlling state machine for the program.
     * 
     * @param currentState the current state of the state machine
     * @return the new state of the state machine
     */
    gameState dealWithCurrentState(gameState currentState);

    /**
     * @brief Takes the current guessed values and sets the LEDs
     * 
     */
    void setLedsStates();

    //--------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------
    // TODO delete everything below this comment when switching to hardware

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
     * @return string to print to the screen
     */
    std::string getColourText(ledColour colour);
};