#include <SDL2/SDL.h>

#include "EventHandler.h"

namespace control
{
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
        this->onKeyDown();
    }
    else if (event.type == SDL_KEYUP)
    {
        this->onKeyUp();
    }
}
} // namespace control
