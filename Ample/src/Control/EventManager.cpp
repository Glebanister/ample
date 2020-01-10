#include <SDL2/SDL.h>
#include <stdexcept>

#include "EventHandler.h"
#include "EventManager.h"
#include "OsManager.h"

namespace control
{
EventManager::EventManager()
{
    keyboard = new KeyboardManager;
    manager = new os::OsManager;
    this->handlerByType[SDL_KEYDOWN].push_back(keyboard);
    this->handlerByType[SDL_KEYUP].push_back(keyboard);
}

void EventManager::update()
{
    while (SDL_PollEvent(&this->ev))
    {
        for (auto handler : this->handlerByType[this->ev.type])
        {
            handler->handleEvent(this->ev);
        }
    }
}

void EventManager::addKeyHandler(const key_t &key, KeyHandler *handler)
{
    keyboard->addKeyHandler(key, handler);
}

void EventManager::addEventHandler(const int &eventType, EventHandler *handler)
{
    this->handlerByType[eventType].push_back(handler);
}

void EventManager::clearType(const int &eventType)
{
    this->handlerByType[eventType].clear();
}

void EventManager::KeyboardManager::addKeyHandler(const key_t &key, KeyHandler *handler)
{
    if (!handler)
    {
        throw std::runtime_error(errEventManagerMessage[ERR_EMPTY_HANDLER]);
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

EventManager::~EventManager()
{
    delete keyboard;
    delete manager;
}
} // namespace control
