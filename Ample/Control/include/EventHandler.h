#pragma once

#include <SDL2/SDL.h>

namespace control
{
class EventHandler
{
public:
    virtual void handleEvent(const SDL_Event &event) = 0;
};

class KeyHandler : public EventHandler
{
public:
    virtual void onKeyDown();
    virtual void onKeyUp();

    void handleEvent(const SDL_Event &event) override;
};
} // namespace control
