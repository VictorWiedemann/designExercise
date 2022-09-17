#include "buttons.h"
#include <iostream>
#include <stdint.h>

//TODO remove ncurses when we move to real hardware
#include <ncurses.h>

constexpr uint8_t NUM_OF_BUTTONS = 3;

// ASSUMPTION: there are only 3 button IDs
typedef struct buttonsInfo
{
    char buttonId;
}buttonsInfo;

//ASSUMPTION: Check the readme for more details. Assuming that the deviceTree will have a single device tree item for all 3 buttons.
//This makes it way easier to program around in a single threaded application.
//If I were to have 3 seperate device tree items, I would have to do some polling or multithreaded work to feel responsive.
Buttons::Buttons()
{
    buttonsInfo buttons[NUM_OF_BUTTONS] = 
    {
        {.buttonId = 'A'},
        {.buttonId = 'B'},
        {.buttonId = 'C'}
    };
}


Buttons::~Buttons()
{
    
}

/**
 * @brief Get the Led Colour object
 *
 * @return ledColour - the enum value of which color the led currently is
 */
char Buttons::getButtonInput()
{
    return getch(); 
}