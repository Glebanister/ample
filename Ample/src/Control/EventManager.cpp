#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>

#include "EventHandler.h"
#include "EventManager.h"

namespace control
{
EventManager::EventManager()
    : keyboard(std::make_unique<KeyboardManager>())
{
    handlerByType[SDL_KEYDOWN].push_back(*keyboard);
    handlerByType[SDL_KEYUP].push_back(*keyboard);
}

void EventManager::update()
{
    while (SDL_PollEvent(&ev))
    {
        for (auto handler : this->handlerByType[this->ev.type])
        {
            handler->handleEvent(this->ev);
        }
    }
}

void EventManager::addKeyHandler(const key_t key, KeyHandler &handler)
{
    keyboard->addKeyHandler(key, handler);
}

void EventManager::addEventHandler(const int eventType, EventHandler &handler)
{
    handlerByType[eventType].push_back(handler);
}

void EventManager::clearType(const int &eventType)
{
    handlerByType[eventType].clear();
}

void KeyboardManager::addKeyHandler(const key_t key, KeyHandler &handler)
{
    handlers[key].push_back(handler);
}

void KeyboardManager::clearKey(const key_t key)
{
    handlers[key].clear();
}

void KeyboardManager::handleEvent(const SDL_Event &event)
{
    for (EventHandler &handler : handlers[event.key.keysym.sym])
    {
        handler.handleEvent(event);
    }
}
} // namespace control
