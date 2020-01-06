#include <SDL2/SDL.h>
#include <stdexcept>

#include "EventHandler.h"
#include "EventManager.h"

namespace control
{
EventManager::EventManager()
{
    if (!SDL_WasInit(SDL_INIT_EVERYTHING))
    {
        throw std::logic_error(__PRETTY_FUNCTION__);
    }
    this->addKeyboard();
}

void EventManager::update()
{
    while (SDL_PollEvent(&this->ev))
    {
        if (this->handlerByType[this->ev.type])
        {
            this->handlerByType[this->ev.type]->handleEvent(this->ev);
        }
    }
}

void EventManager::addKeyHandler(const key_t &key, KeyHandler *handler)
{
    keyboard->addKeyHandler(key, handler);
}

EventManager::~EventManager()
{
    delete keyboard;
}

void EventManager::KeyboardManager::addKeyHandler(const key_t &key, KeyHandler *handler)
{
    if (!handler)
    {
        throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    this->handlers[key].push_back(handler);
}

void EventManager::KeyboardManager::clearKey(const key_t &key)
{
    this->handlers[key].clear();
}

void EventManager::KeyboardManager::handleEvent(const SDL_Event &event)
{
    for (auto handler : this->handlers[event.key.keysym.sym])
    {
        handler->handleEvent(event);
    }
}

void EventManager::addKeyboard()
{
    keyboard = new KeyboardManager;
    this->handlerByType[SDL_KEYDOWN] = keyboard;
    this->handlerByType[SDL_KEYUP] = keyboard;
}
} // namespace control
