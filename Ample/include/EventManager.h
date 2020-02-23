#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

#include "EventHandler.h"
#include "EventManager.h"
#include "Vector2d.h"

namespace ample::control
{
using Event = SDL_Event;

class KeyboardManager : public EventHandler
{
public:
    void addKeyHandler(const keysym key, KeyHandler &handler);
    void clearKey(const keysym key);
    void handleEvent(const SDL_Event &event) override;

private:
    std::unordered_map<int32_t, std::vector<std::shared_ptr<KeyHandler>>> _handlers;
};

class EventManager final
{
public:
    EventManager();
    EventManager(const EventManager &other) = delete;

    EventManager &operator=(const EventManager &other) = delete;

    void update();

    void addKeyHandler(const keysym key, KeyHandler &handler);
    void addEventHandler(const int eventType, EventHandler &handler);
    void clearType(const int &eventType);

    ~EventManager() = default;

private:
    SDL_Event ev;
    std::unordered_map<int, std::vector<std::shared_ptr<EventHandler>>> _handlerByType;
    std::shared_ptr<KeyboardManager> _keyboard;
    std::shared_ptr<MouseHandler> _mouse;
};
} // namespace control
