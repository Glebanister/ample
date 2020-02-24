#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>

#include "EventHandler.h"
#include "EventManager.h"

namespace ample::control
{
EventManager::EventManager(window::Window &window)
    : _keyboard(std::make_shared<KeyboardManager>()),
      _mouse(std::make_shared<MouseHandler>()),
      _window(window)
{
    _handlerByType[SDL_KEYDOWN].push_back(_keyboard);
    _handlerByType[SDL_KEYUP].push_back(_keyboard);
    _handlerByType[SDL_MOUSEBUTTONDOWN].push_back(_mouse);
    _handlerByType[SDL_MOUSEBUTTONUP].push_back(_mouse);
    _handlerByType[SDL_MOUSEWHEEL].push_back(_mouse);
    _handlerByType[SDL_MOUSEMOTION].push_back(_mouse);
}

void EventManager::update()
{
    _mouse->clear();
    _keyboard->clear();
    while (SDL_PollEvent(&ev))
    {
        for (auto &handler : _handlerByType[ev.type])
        {
            handler->handleEvent(this->ev);
        }
    }
}

void EventManager::addKeyHandler(const keysym key, std::shared_ptr<KeyHandler> handler)
{
    _keyboard->addKeyHandler(key, handler);
}

void EventManager::addEventHandler(const int eventType, std::shared_ptr<EventHandler> handler)
{
    _handlerByType[eventType].push_back(handler);
}

void EventManager::clearType(const int &eventType)
{
    _handlerByType[eventType].clear();
}

std::shared_ptr<KeyboardManager> EventManager::keyboard() const
{
    return _keyboard;
}
std::shared_ptr<MouseHandler> EventManager::mouse() const
{
    return _mouse;
}

void KeyboardManager::addKeyHandler(const keysym key, std::shared_ptr<KeyHandler> handler)
{
    _handlers[key].push_back(handler);
}

void KeyboardManager::clearKey(const keysym key)
{
    _handlers[key].clear();
}

void KeyboardManager::handleEvent(const SDL_Event &event)
{
    _keymapWasDown[event.key.keysym.sym] = event.type;
    _keymapWasUp[event.key.keysym.sym] = event.type;
    _keymapPressed[event.key.keysym.sym] = event.type;
    for (auto &handler : _handlers[event.key.keysym.sym])
    {
        handler->handleEvent(event);
    }
}

bool KeyboardManager::isKeyPressed(keysym key)
{
    return _keymapWasDown[key] == KEY_DOWN;
}

bool KeyboardManager::isKeyReleased(keysym key)
{
    return _keymapWasUp[key] == KEY_UP;
}

bool KeyboardManager::isKeyDown(keysym key)
{
    return _keymapPressed[key] == KEY_DOWN;
}

void KeyboardManager::clear()
{
    _keymapWasDown.clear();
    _keymapWasUp.clear();
}
} // namespace ample::control
