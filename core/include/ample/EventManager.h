#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

#include "EventHandler.h"
#include "EventManager.h"
#include "Vector2d.h"
#include "Window.h"
#include "Singleton.h"
#include "Noncopyable.h"

namespace ample::control
{
using Event = SDL_Event;

class KeyboardManager final : public EventHandler
{
public:
    enum scancodes
    {
        C_TAB = SDL_SCANCODE_TAB,
        C_LEFT = SDL_SCANCODE_LEFT,
        C_RIGHT = SDL_SCANCODE_RIGHT,
        C_UP = SDL_SCANCODE_UP,
        C_DOWN = SDL_SCANCODE_DOWN,
        C_PAGEUP = SDL_SCANCODE_PAGEUP,
        C_PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
        C_HOME = SDL_SCANCODE_HOME,
        C_END = SDL_SCANCODE_END,
        C_INSERT = SDL_SCANCODE_INSERT,
        C_DELETE = SDL_SCANCODE_DELETE,
        C_BACKSPACE = SDL_SCANCODE_BACKSPACE,
        C_SPACE = SDL_SCANCODE_SPACE,
        C_ENTER = SDL_SCANCODE_RETURN,
        C_ESCAPE = SDL_SCANCODE_ESCAPE,
        C_KP_ENTER = SDL_SCANCODE_KP_ENTER,
        A = SDL_SCANCODE_A,
        C = SDL_SCANCODE_C,
        V = SDL_SCANCODE_V,
        X = SDL_SCANCODE_X,
        Y = SDL_SCANCODE_Y,
        Z = SDL_SCANCODE_Z,
    };

private:
    struct Modificators
    {
        bool leftShift() const noexcept;
        bool rightShift() const noexcept;
        bool shift() const noexcept;
        bool leftAlt() const noexcept;
        bool rightAlt() const noexcept;
        bool alt() const noexcept;
        bool leftCtrl() const noexcept;
        bool rightCtrl() const noexcept;
        bool ctrl() const noexcept;
        bool caps() const noexcept;
        void clear();

        bool _shift, _lShiftDown, _rShiftDown;
        bool _alt, _lAltDown, _rAltDown;
        bool _ctrl, _lCtrlDown, _rCtrlDown;
        bool _caps;
    };

public:
    void addKeyHandler(const keysym key, KeyHandler &handler);
    void clearKey(const keysym key);
    void handleEvent(const SDL_Event &event) override;
    bool isKeyPressed(keysym key);
    bool isKeyReleased(keysym key);
    bool isKeyDown(keysym key);
    bool scancode(scancodes scancode);
    void clear();
    char getChar() const noexcept;
    const Modificators &modificators() const noexcept;
    bool getPressedScancode() const noexcept;

private:
    std::unordered_map<int32_t, std::vector<KeyHandler *>> _handlers;
    std::unordered_map<int32_t, int32_t> _keymapWasUp;
    std::unordered_map<int32_t, int32_t> _keymapWasDown;
    std::unordered_map<int32_t, int32_t> _keymapPressed;
    std::unordered_map<int32_t, int32_t> _scancodePressed;
    Modificators _mods;

    char _char;
    uint32_t _scancode;

};

class EventManager : public utils::Singleton<EventManager>, public utils::Noncopyable
{
public:

    void update();

    void addKeyHandler(const keysym key, KeyHandler &handler);
    void addEventHandler(const int eventType, EventHandler &handler);
    void clearType(const int &eventType);

    KeyboardManager &keyboard();
    MouseHandler &mouse();

    std::vector<SDL_Event> &events() noexcept;

protected:
    EventManager();
    std::shared_ptr<KeyboardManager> _keyboard;
    std::shared_ptr<MouseHandler> _mouse;
    std::vector<SDL_Event> _events;

    std::unordered_map<int, std::vector<EventHandler *>> _handlerByType;
};
} // namespace ample::control
