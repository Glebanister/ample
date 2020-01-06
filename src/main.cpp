#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <SDL2/SDL.h>

#include "Storage.h"
#include "Condition.h"
#include "Activity.h"

namespace control
{
class EventHandler
{
public:
    virtual void handleEvent(const SDL_Event &event) = 0;
};

class KeyHandler final : public EventHandler
{
public:
    KeyHandler() = delete;
    KeyHandler(const key_t &trigger)
        : trigger(trigger) {}

    virtual void onKeyDown();
    virtual void onKeyUp();

    void handleEvent(const SDL_Event &event) override
    {
        if (event.type == SDL_KEYDOWN)
        {
            this->onKeyDown();
        }
        else if (event.type == SDL_KEYUP)
        {
            this->onKeyUp();
        }
    }

private:
    key_t trigger;
};

class KeyboardManager final : public EventHandler
{
public:
    void addKeyHandler(const key_t &key, KeyHandler *handler)
    {
        if (!handler)
        {
            throw std::runtime_error(__PRETTY_FUNCTION__);
        }
        handlers[key].push_back(handler);
    }

    void clearKey(const key_t &key)
    {
        handlers[key].clear();
    }

    void handleEvent(const SDL_Event &event) override
    {
        for (auto handler : handlers[event.key.keysym.sym])
        {
            handler->handleEvent(event);
        }
    }

private:
    std::unordered_map<key_t, std::vector<KeyHandler *>> handlers;
};

class EventManager final
{
public:
    EventManager()
    {
        if (!SDL_WasInit(SDL_INIT_EVERYTHING))
        {
            throw std::logic_error(__PRETTY_FUNCTION__);
        }
        this->addKeyboard();
    }

    void update()
    {
        while (SDL_PollEvent(&this->ev))
        {
            if (this->handlerByType[this->ev.type])
            {
                this->handlerByType[this->ev.type]->handleEvent(this->ev);
            }
        }
    }

    void addKeyHandler(const key_t &key, KeyHandler *handler)
    {
        keyboard->addKeyHandler(key, handler);
    }
    ~EventManager()
    {
        delete keyboard;
    }

private:
    SDL_Event ev;
    KeyboardManager *keyboard;
    std::unordered_map<int, EventHandler *> handlerByType;

    // TODO commented events

    void addKeyboard()
    {
        keyboard = new KeyboardManager;
        handlerByType[SDL_KEYDOWN] = keyboard;
        handlerByType[SDL_KEYUP] = keyboard;
    }
};

} // control

namespace keyboard
{
int w = SDLK_w;
int a = SDLK_a;
int s = SDLK_s;
int d = SDLK_d;
} // namespace keyboard

int main()
{
    return 0;
}
