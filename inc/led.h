#pragma once

#include <stdint.h>

constexpr uint8_t NUM_OF_LEDS  = 3;

typedef enum ledColour
{
    LED_OFF = 0,
    LED_RED,
    LED_ORANGE,
    LED_GREEN,
    NUM_OF_LED_COLOURS,
} ledColour;

enum
{
    LED_OK = 0,
    LED_CANNOT_SET,
};

class Led
{

public:
    Led(uint8_t ledNum);
    ~Led();

    /**
     * @brief Set the Led Colour object
     *
     * @param newColour - the enum value of which color to change the led to
     */
    int setLedColour(ledColour newColour);

    /**
     * @brief Get the Led Colour object
     *
     * @return ledColour - the enum value of which color the led currently is
     */
    ledColour getLedColour();

private:
    ledColour currentColour;
    int ledNumber;

    int setLedColourHardware();
};


