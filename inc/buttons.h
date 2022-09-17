#pragma once

#include <stdint.h>

enum
{
    BUTTON_OK = 0,
};

typedef enum buttonPressed
{
    BUTTON_A,
    BUTTON_B,
    BUTTON_C,
    NUM_OF_PLAYABLE_BUTTONS,
    BUTTON_NOT_PRESSED,
    BUTTON_ESCAPE,
}buttonPressed;

class Buttons
{

public:
    Buttons();
    ~Buttons();

    /**
     * @brief Blocking call to get the latest button Input
     * //TODO consider making this input be non-blocking later if other actions are needed
     * in a production setting. Maybe a timeout in a loop to check for ctrl+c
     */
    buttonPressed getButtonInput();

private:

};