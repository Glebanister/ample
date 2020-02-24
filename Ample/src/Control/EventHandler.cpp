#include <SDL2/SDL.h>
#include <iostream>

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
    _position = {event.motion.x, event.motion.y};
    switch (event.type)
    {
    case MOUSEMOTION:
        onMotion();
        break;
    case MOUSEWHEEL:
        _wheel = {event.wheel.x, event.wheel.y};
        onWheel();
        break;
    case MOUSEBUTTON_DOWN:
        switch (event.button.button)
        {
        case mouseButton::BUTTON_LEFT:
            _leftDown = true;
            _leftPressed = true;
            break;
        case mouseButton::BUTTON_RIGHT:
            _rightDown = true;
            _rightPressed = true;
            break;
        case mouseButton::BUTTON_MIDDLE:
            _middleDown = true;
            _middlePressed = true;
            break;
        }
        onButtonDown();
        break;
    case MOUSEBUTTON_UP:
        switch (event.button.button)
        {
        case mouseButton::BUTTON_LEFT:
            _leftDown = false;
            _leftReleased = true;
            break;
        case mouseButton::BUTTON_RIGHT:
            _rightDown = false;
            _rightReleased = true;
            break;
        case mouseButton::BUTTON_MIDDLE:
            _middleDown = false;
            _middleReleased = true;
            break;
        }
        onButtonUp();
        break;
    }
}

pixel_t MouseHandler::getMouseX() const
{
    return _position.x;
}

pixel_t MouseHandler::getMouseY() const
{
    return _position.y;
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

bool MouseHandler::isSingle() const
{
    return _event.button.clicks == 1;
}

int32_t MouseHandler::getWheelX() const
{
    return _wheel.x;
}

int32_t MouseHandler::getWheelY() const
{
    return _wheel.y;
}

bool MouseHandler::isLeftPressed() const
{
    return _leftPressed;
}
bool MouseHandler::isLeftReleased() const
{
    return _leftReleased;
}
bool MouseHandler::isLeftDown() const
{
    return _leftDown;
}

bool MouseHandler::isRightPressed() const
{
    return _rightPressed;
}
bool MouseHandler::isRightReleased() const
{
    return _rightReleased;
}
bool MouseHandler::isRightDown() const
{
    return _rightDown;
}

bool MouseHandler::isMiddlePressed() const
{
    return _middlePressed;
}
bool MouseHandler::isMiddleReleased() const
{
    return _middleReleased;
}
bool MouseHandler::isMiddleDown() const
{
    return _middleDown;
}

void MouseHandler::clear()
{
    _event = Event();
    _leftPressed = _leftReleased = false;
    _rightPressed = _rightReleased = false;
    _middlePressed = _middleReleased = false;
    _wheel = {0, 0};
}

void MouseHandler::onButtonDown() {}
void MouseHandler::onButtonUp() {}
void MouseHandler::onMotion() {}
void MouseHandler::onWheel() {}
} // namespace ample::control
