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

void KeyHandler::handleEvent(const SDL_Event &event)
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

int KeyHandler::getStatus()
{
    return this->pressed;
}

} // namespace control
