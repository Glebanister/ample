#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>

#include "EventHandler.h"
#include "EventManager.h"
#include "Debug.h"
#include "SDLEnvironment.h"

namespace ample::control
{
EventManager::EventManager()
    : _keyboard(std::make_shared<KeyboardManager>()),
      _mouse(std::make_shared<MouseHandler>())
{
    os::environment::SDLEnvironment::instance();
    _handlerByType[SDL_KEYDOWN].push_back(_keyboard);
    _handlerByType[SDL_KEYUP].push_back(_keyboard);
    _handlerByType[SDL_MOUSEBUTTONDOWN].push_back(_mouse);
    _handlerByType[SDL_MOUSEBUTTONUP].push_back(_mouse);
    _handlerByType[SDL_MOUSEWHEEL].push_back(_mouse);
    _handlerByType[SDL_MOUSEMOTION].push_back(_mouse);
}

void EventManager::update()
{
    _mouse->clear();
    _keyboard->clear();
    _events.clear();
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        _events.push_back(ev);
        for (auto &handler : _handlerByType[ev.type])
        {
            assert(handler);
            handler->handleEvent(_events.back());
        }
    }
}

std::vector<SDL_Event> &EventManager::events() noexcept
{
    return _events;
}

void EventManager::addEventHandler(const int eventType, std::shared_ptr<EventHandler> handler)
{
    _handlerByType[eventType].push_back(handler);
}

void EventManager::clearType(const int &eventType)
{
    _handlerByType[eventType].clear();
}

bool KeyboardManager::Modificators::leftShift() const noexcept { return _lShiftDown; }
bool KeyboardManager::Modificators::rightShift() const noexcept { return _rShiftDown; }
bool KeyboardManager::Modificators::shift() const noexcept { return _shift; }
bool KeyboardManager::Modificators::leftAlt() const noexcept { return _lAltDown; }
bool KeyboardManager::Modificators::rightAlt() const noexcept { return _rAltDown; }
bool KeyboardManager::Modificators::alt() const noexcept { return _alt; }
bool KeyboardManager::Modificators::leftCtrl() const noexcept { return _lCtrlDown; }
bool KeyboardManager::Modificators::rightCtrl() const noexcept { return _rCtrlDown; }
bool KeyboardManager::Modificators::ctrl() const noexcept { return _ctrl; }
bool KeyboardManager::Modificators::caps() const noexcept { return _caps; }
void KeyboardManager::Modificators::clear()
{
    _shift = _lShiftDown = _rShiftDown = false;
    _alt = _lAltDown = _rAltDown = false;
    _ctrl = _lCtrlDown = _rCtrlDown = false;
    _caps = false;
}

KeyboardManager &EventManager::keyboard()
{
    return *_keyboard;
}
MouseHandler &EventManager::mouse()
{
    return *_mouse;
}

void KeyboardManager::addKeyHandler(const keysym key, std::shared_ptr<KeyHandler> handler)
{
    _handlers[key].push_back(handler);
}

void KeyboardManager::clearKey(const keysym key)
{
    _handlers[key].clear();
}

bool KeyboardManager::getPressedScancode() const noexcept
{
    return _scancode;
}

void KeyboardManager::handleEvent(const SDL_Event &event)
{
    _keymapWasDown[event.key.keysym.scancode] = event.type;
    _keymapWasUp[event.key.keysym.scancode] = event.type;
    _keymapPressed[event.key.keysym.scancode] = event.type;
    if (event.type == KEY_DOWN)
    {
        _char = event.key.keysym.sym;
    }
    _scancode = event.key.keysym.scancode;
    for (auto &handler : _handlers[event.key.keysym.scancode])
    {
        handler->handleEvent(event);
    }
    {
        auto mod = event.key.keysym.mod;
        if (mod & KMOD_NUM)
        {
        }
        if (mod & KMOD_CAPS)
        {
            _mods._caps = true;
        }
        if (mod & KMOD_LCTRL)
        {
            _mods._lCtrlDown = true;
        }
        if (mod & KMOD_RCTRL)
        {
            _mods._rCtrlDown = true;
        }
        if (mod & KMOD_RSHIFT)
        {
            _mods._rShiftDown = true;
        }
        if (mod & KMOD_LSHIFT)
        {
            _mods._lShiftDown = true;
        }
        if (mod & KMOD_RALT)
        {
            _mods._rAltDown = true;
        }
        if (mod & KMOD_LALT)
        {
            _mods._lAltDown = true;
        }
        if (mod & KMOD_CTRL)
        {
            _mods._ctrl = true;
        }
        if (mod & KMOD_SHIFT)
        {
            _mods._shift = true;
        }
        if (mod & KMOD_ALT)
        {
            _mods._alt = true;
        }
    }
}

bool KeyboardManager::isKeyPressed(keysym key)
{
    return _keymapWasDown[key] == KEY_DOWN;
}

bool KeyboardManager::isKeyReleased(keysym key)
{
    return _keymapWasUp[key] == KEY_UP;
}

bool KeyboardManager::isKeyDown(keysym key)
{
    return _keymapPressed[key] == KEY_DOWN;
}

bool KeyboardManager::scancode(scancodes scancode)
{
    return _scancodePressed[scancode] == KEY_DOWN;
}

const KeyboardManager::Modificators &KeyboardManager::modificators() const noexcept
{
    return _mods;
}

void KeyboardManager::clear()
{
    _keymapWasDown.clear();
    _keymapWasUp.clear();
    _scancodePressed.clear();
    _mods.clear();
    _char = '\0';
    _scancode = 0;
}

char KeyboardManager::getChar() const noexcept
{
    static std::unordered_map<char, char> shifted = {
        {'a', 'A'},
        {'b', 'B'},
        {'c', 'C'},
        {'d', 'D'},
        {'e', 'E'},
        {'f', 'F'},
        {'g', 'G'},
        {'h', 'H'},
        {'i', 'I'},
        {'k', 'K'},
        {'l', 'L'},
        {'m', 'M'},
        {'n', 'N'},
        {'o', 'O'},
        {'p', 'P'},
        {'q', 'Q'},
        {'r', 'R'},
        {'s', 'S'},
        {'t', 'T'},
        {'u', 'U'},
        {'v', 'V'},
        {'w', 'W'},
        {'x', 'X'},
        {'y', 'Y'},
        {'z', 'Z'},
        {'1', '!'},
        {'2', '@'},
        {'3', '#'},
        {'4', '$'},
        {'5', '%'},
        {'6', '^'},
        {'7', '&'},
        {'8', '*'},
        {'9', '('},
        {'0', ')'},
        {'[', '{'},
        {']', '}'},
        {';', ':'},
        {'\'', '"'},
        {',', '<'},
        {'.', '>'},
        {'/', '?'},
        {'`', '~'},
        {' ', ' '},
        {'-', '_'},
        {'=', '+'},
        {'\\', '|'},
        {'\n', '\n'},
    };
    if (!(shifted[_char]))
    {
        return 0;
    }
    if (modificators().shift() || modificators().caps())
    {
        return shifted[_char];
    }
    return _char;
}
} // namespace ample::control
