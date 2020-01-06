#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>

namespace control
{
class EventManager final
{
public:
    EventManager();

    void update();
    void addKeyHandler(const key_t &key, KeyHandler *handler);

    ~EventManager();

private:

    class KeyboardManager final : public EventHandler
    {
    public:
        void addKeyHandler(const key_t &key, KeyHandler *handler);
        void clearKey(const key_t &key);
        void handleEvent(const SDL_Event &event) override;

    private:
        std::unordered_map<key_t, std::vector<KeyHandler *>> handlers;
    };

    SDL_Event ev;
    KeyboardManager *keyboard;
    std::unordered_map<int, EventHandler *> handlerByType;

    // TODO commented events

    void addKeyboard();
};
} // namespace control
