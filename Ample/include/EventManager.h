#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "EventHandler.h"
#include "EventManager.h"

namespace control
{
typedef SDL_Event Event;

class EventManager final
{
public:
    EventManager();
    EventManager(const EventManager &other) = delete;

    EventManager &operator=(const EventManager &other) = delete;

    void update();

    void addKeyHandler(const key_t &key, KeyHandler *handler);
    void addEventHandler(const int &eventType, EventHandler *handler);
    void clearType(const int &eventType);

    ~EventManager();

private:
    class KeyboardManager : public EventHandler
    {
    public:
        void addKeyHandler(const key_t &key, KeyHandler *handler);
        void clearKey(const key_t &key);
        void handleEvent(const SDL_Event &event) override;

    private:
        std::unordered_map<key_t, std::vector<KeyHandler *>> handlers;
    };

    SDL_Event ev;
    std::unordered_map<int, std::vector<EventHandler *>> handlerByType;

    KeyboardManager *keyboard;
};
} // namespace control
