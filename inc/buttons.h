#pragma once

#include <stdint.h>

enum
{
    BUTTON_OK = 0,
};

class Buttons
{

public:
    Buttons();
    ~Buttons();

    /**
     * @brief Blocking call to get the latest button Input
     * //TODO make this input be non-blocking later in a production setting. Maybe a timeout in a loop to check for ctrl+c
     */
    char getButtonInput();

private:

};