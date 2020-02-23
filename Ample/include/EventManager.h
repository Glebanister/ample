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

class KeyboardManager final : public EventHandler
{
public:
    void addKeyHandler(const keysym key, std::shared_ptr<KeyHandler> handler);
    void clearKey(const keysym key);
    void handleEvent(const SDL_Event &event) override;
    bool keyIsDown(keysym key);

private:
    std::unordered_map<int32_t, std::vector<std::shared_ptr<KeyHandler>>> _handlers;
    std::unordered_map<int32_t, int32_t> _keymap;
};

class EventManager final
{
public:
    EventManager();
    EventManager(const EventManager &other) = delete;

    EventManager &operator=(const EventManager &other) = delete;

    void update();

    void addKeyHandler(const keysym key, std::shared_ptr<KeyHandler> handler);
    void addEventHandler(const int eventType, std::shared_ptr<EventHandler> handler);
    void clearType(const int &eventType);

    bool keyIsDown(keysym key) const;
    pixel_t getMouseX() const;
    pixel_t getMouseY() const;
    pixel_t getMouseXRel() const;
    pixel_t getMouseYRel() const;
    int32_t getWheelX() const;
    int32_t getWheelY() const;
    bool isDoubleClick() const;

    ~EventManager() = default;

private:
    SDL_Event ev;
    std::unordered_map<int, std::vector<std::shared_ptr<EventHandler>>> _handlerByType;
    std::shared_ptr<KeyboardManager> _keyboard;
    std::shared_ptr<MouseHandler> _mouse;
};
} // namespace ample::control
