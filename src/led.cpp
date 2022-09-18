#include "led.h"
#include <iostream>
#include <stdint.h>

Led::Led(uint8_t ledNum)
{
    if(ledNum > NUM_OF_LEDS || ledNum == 0)
    {
        std::cout << "error, given LED number " << (int)ledNum << " is out of range" << std::endl;
        std::cout << "This will not connect to any hardware" << std::endl;
        //TODO decide what kind of error handling is best for target hardware
        exit(-1);
    }
    ledNumber = ledNum;
    currentColour = LED_OFF;

    //TODO set this up to hardware see `setLedColourHardware` for notes
}

Led::~Led()
{
}

int Led::setLedColour(ledColour newColour)
{
    if((newColour < 0) || (newColour >= NUM_OF_LED_COLOURS))
    {
        std::cout << "error, color on led number " << ledNumber;
        return LED_CANNOT_SET;
    }
    
    currentColour = newColour;

    //TODO SET LED HERE. THIS WILL BE UPDATED WITH THE MOVE TO HARDWARE
    if(setLedColourHardware() != LED_OK)
    {
        //Do something with the error here. May depend on hardware implementation
    }

    return LED_OK;
}

ledColour Led::getLedColour()
{
    return currentColour;
}

int Led::setLedColourHardware(){
//TODO future work:
/**
 * for the move to hardware, I suspect there will be a map here for led ID and file handle
 * the file handle will indicate where to change the state of the LED in hardware
 * There is also likely a translation from ledColour to the coded value to write into the
 * led file handle. Without more details, I willl leave this area blank  
 * 
 */
    return LED_OK;
}