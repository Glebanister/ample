#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>

#include "EventHandler.h"
#include "EventManager.h"

namespace ample::control
{
EventManager::EventManager()
    : _keyboard(std::make_shared<KeyboardManager>()),
      _mouse(std::make_shared<MouseHandler>())
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
    while (SDL_PollEvent(&ev))
    {
        for (auto &handler : _handlerByType[ev.type])
        {
            handler->handleEvent(this->ev);
        }
    }
}

void EventManager::addKeyHandler(const keysym key, KeyHandler &handler)
{
    _keyboard->addKeyHandler(key, handler);
}

void EventManager::addEventHandler(const int eventType, EventHandler &handler)
{
    _handlerByType[eventType].push_back(std::make_shared<EventHandler>(handler));
}

void EventManager::clearType(const int &eventType)
{
    _handlerByType[eventType].clear();
}

void KeyboardManager::addKeyHandler(const keysym key, KeyHandler &handler)
{
    _handlers[key].push_back(std::make_shared<KeyHandler>(handler));
}

void KeyboardManager::clearKey(const keysym key)
{
    _handlers[key].clear();
}

void KeyboardManager::handleEvent(const SDL_Event &event)
{
    for (auto &handler : _handlers[event.key.keysym.sym])
    {
        handler->handleEvent(event);
    }
}
} // namespace control
