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

typedef enum guesses{
    GUESS_EMPTY,
    GUESS_CORRECT,
    GUESS_DIFF_SPOT,
    GUESS_WRONG,
}guesses;

class Game
{

public:
    Game(bool isDebug = false);
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
    guesses userGuesses[NUM_OF_LEDS];
    bool debugMode;

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
    gameState checkGuess(buttonPressed buttonRecv, int quessLocation);

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

    /**
     * @brief checks to see if the guessed input is in the sequence
     *
     * @param buttonRecv the user-entered value to compare against
     * @return if the guess shows up in the sequence
     */
    bool isInSequence(buttonPressed buttonRecv);

    /**
     * @brief checks to see if the game was won.
     *
     * @return the state of GAME_WIN or GAME_RETRY;
     */
    gameState setGameEndState();

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
     * @brief prints the debug information to assist in development.
     *
     */
    void printDebugInfo();

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