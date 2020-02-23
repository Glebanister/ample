#include <SDL2/SDL.h>

#include "EventHandler.h"

namespace ample::control
{
KeyHandler::KeyHandler()
{
    this->pressed = eventType::KEY_UP;
}

void KeyHandler::onKeyDown()
{
    return;
}

void KeyHandler::onKeyUp()
{
    return;
}

int KeyHandler::getStatus() const
{
    return this->pressed;
}

void KeyHandler::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        this->onKeyDown();
        this->pressed = eventType::KEY_DOWN;
    }
    else if (event.type == SDL_KEYUP)
    {
        this->onKeyUp();
        this->pressed = eventType::KEY_UP;
    }
}

KeyHandlerSingleDown::KeyHandlerSingleDown()
    : KeyHandler() {}

void KeyHandlerSingleDown::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (this->pressed == eventType::KEY_UP)
        {
            this->onKeyDown();
        }
        this->pressed = eventType::KEY_DOWN;
    }
    else if (event.type == SDL_KEYUP)
    {
        if (this->pressed == eventType::KEY_DOWN)
        {
            this->onKeyUp();
        }
        this->pressed = eventType::KEY_UP;
    }
}

void MouseHandler::handleEvent(const SDL_Event &event)
{
    _event = event;
    switch (event.type)
    {
    case MOUSEMOTION:
        onMotion();
        break;
    case MOUSEWHEEL:
        onWheel();
        break;
    case MOUSEBUTTON_DOWN:
        onButtonDown();
        break;
    case MOUSEBUTTON_UP:
        onButtonUp();
        break;
    }
}

pixel_t MouseHandler::getMouseX() const
{
    return _event.motion.x;
}

pixel_t MouseHandler::getMouseY() const
{
    return _event.motion.y;
}

pixel_t MouseHandler::getMouseXRel() const
{
    return _event.motion.xrel;
}

pixel_t MouseHandler::getMouseYRel() const
{
    return _event.motion.yrel;
}

bool MouseHandler::isDouble() const
{
    return _event.button.clicks == 2;
}

int32_t MouseHandler::getWheelX() const
{
    return _event.wheel.x;
}

int32_t MouseHandler::getWheelY() const
{
    return _event.wheel.y;
}

void MouseHandler::onButtonDown() {}
void MouseHandler::onButtonUp() {}
void MouseHandler::onMotion() {}
void MouseHandler::onWheel() {}
} // namespace ample::control
