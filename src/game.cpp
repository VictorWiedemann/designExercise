#include "game.h"

#include <iostream>

// TODO remove ncurses when we move to actual hardware
#include <ncurses.h>
#include <stdlib.h>

Game::Game()
{
    std::cout << "hello world" << std::endl;
    for (int i = 1; i <= NUM_OF_LEDS; i++)
    {
        // off by one because we want to label the leds 1-3, but store them 0-2
        Leds[i - 1] = new Led(i);
    }

    inputButtons = new Buttons;
}

Game::~Game()
{
    for (Led *eachLed : Leds)
    {
        delete eachLed;
    }

    delete inputButtons;
}

uint8_t Game::startGame()
{
    try
    {        
        for(int i = 0; i < NUM_OF_LEDS; i++)
        {
            this->refreshScreen();   
        }
    }
    catch (int error)
    {
        return GAME_UNEXPECTED_ERROR;
    }

    return GAME_CLOSED_NORMALLY;
}

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