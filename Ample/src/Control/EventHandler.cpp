#include <SDL2/SDL.h>

#include "EventHandler.h"

namespace control
{
KeyHandler::KeyHandler()
{
    this->pressed = event::KEY_UP;
}

void KeyHandler::onKeyDown()
{
    return;
}

void KeyHandler::onKeyUp()
{
    return;
}

int KeyHandler::getStatus()
{
    return this->pressed;
}

void KeyHandler::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        this->onKeyDown();
        this->pressed = event::KEY_DOWN;
    }
    else if (event.type == SDL_KEYUP)
    {
        this->onKeyUp();
        this->pressed = event::KEY_UP;
    }
}

KeyHandlerSingleDown::KeyHandlerSingleDown()
    : KeyHandler() {}

void KeyHandlerSingleDown::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (this->pressed == event::KEY_UP)
        {
            this->onKeyDown();
        }
        this->pressed = event::KEY_DOWN;
    }
    else if (event.type == SDL_KEYUP)
    {
        if (this->pressed == event::KEY_DOWN)
        {
            this->onKeyUp();
        }
        this->pressed = event::KEY_UP;
    }
}
} // namespace control
