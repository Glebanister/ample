#pragma once

#include <SDL2/SDL.h>

#include "Vector2d.h"

namespace ample::control
{
using pixel_t = int32_t;
using Event = SDL_Event;

enum eventType
{
    KEY_DOWN = SDL_KEYDOWN,
    KEY_UP = SDL_KEYUP,
    MOUSEMOTION = SDL_MOUSEMOTION,
    MOUSEWHEEL = SDL_MOUSEWHEEL,
    MOUSEBUTTON_DOWN = SDL_MOUSEBUTTONDOWN,
    MOUSEBUTTON_UP = SDL_MOUSEBUTTONUP
};

enum mouseButton
{
    BUTTON_LEFT = SDL_BUTTON_LEFT,
    BUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
    BUTTON_RIGHT = SDL_BUTTON_RIGHT,
};

enum keysym
{
    UNKNOWN = SDLK_UNKNOWN,
    RETURN = SDLK_RETURN,
    ESCAPE = SDLK_ESCAPE,
    BACKSPACE = SDLK_BACKSPACE,
    TAB = SDLK_TAB,
    SPACE = SDLK_SPACE,
    EXCLAIM = SDLK_EXCLAIM,
    QUOTEDBL = SDLK_QUOTEDBL,
    HASH = SDLK_HASH,
    PERCENT = SDLK_PERCENT,
    DOLLAR = SDLK_DOLLAR,
    AMPERSAND = SDLK_AMPERSAND,
    QUOTE = SDLK_QUOTE,
    LEFTPAREN = SDLK_LEFTPAREN,
    RIGHTPAREN = SDLK_RIGHTPAREN,
    ASTERISK = SDLK_ASTERISK,
    PLUS = SDLK_PLUS,
    COMMA = SDLK_COMMA,
    MINUS = SDLK_MINUS,
    PERIOD = SDLK_PERIOD,
    SLASH = SDLK_SLASH,
    NUM_0 = SDLK_0,
    NUM_1 = SDLK_1,
    NUM_2 = SDLK_2,
    NUM_3 = SDLK_3,
    NUM_4 = SDLK_4,
    NUM_5 = SDLK_5,
    NUM_6 = SDLK_6,
    NUM_7 = SDLK_7,
    NUM_8 = SDLK_8,
    NUM_9 = SDLK_9,
    COLON = SDLK_COLON,
    SEMICOLON = SDLK_SEMICOLON,
    LESS = SDLK_LESS,
    EQUALS = SDLK_EQUALS,
    GREATER = SDLK_GREATER,
    QUESTION = SDLK_QUESTION,
    AT = SDLK_AT,
    /*
       Skip uppercase letters
     */
    LEFTBRACKET = SDLK_LEFTBRACKET,
    BACKSLASH = SDLK_BACKSLASH,
    RIGHTBRACKET = SDLK_RIGHTBRACKET,
    CARET = SDLK_CARET,
    UNDERSCORE = SDLK_UNDERSCORE,
    BACKQUOTE = SDLK_BACKQUOTE,

    KEY_a = SDLK_a,
    KEY_b = SDLK_b,
    KEY_c = SDLK_c,
    KEY_d = SDLK_d,
    KEY_e = SDLK_e,
    KEY_f = SDLK_f,
    KEY_g = SDLK_g,
    KEY_h = SDLK_h,
    KEY_i = SDLK_i,
    KEY_j = SDLK_j,
    KEY_k = SDLK_k,
    KEY_l = SDLK_l,
    KEY_m = SDLK_m,
    KEY_n = SDLK_n,
    KEY_o = SDLK_o,
    KEY_p = SDLK_p,
    KEY_q = SDLK_q,
    KEY_r = SDLK_r,
    KEY_s = SDLK_s,
    KEY_t = SDLK_t,
    KEY_u = SDLK_u,
    KEY_v = SDLK_v,
    KEY_w = SDLK_w,
    KEY_x = SDLK_x,
    KEY_y = SDLK_y,
    KEY_z = SDLK_z,

    CAPSLOCK = SDLK_CAPSLOCK,

    F1 = SDLK_F1,
    F2 = SDLK_F2,
    F3 = SDLK_F3,
    F4 = SDLK_F4,
    F5 = SDLK_F5,
    F6 = SDLK_F6,
    F7 = SDLK_F7,
    F8 = SDLK_F8,
    F9 = SDLK_F9,
    F10 = SDLK_F10,
    F11 = SDLK_F11,
    F12 = SDLK_F12,

    PRINTSCREEN = SDLK_PRINTSCREEN,
    SCROLLLOCK = SDLK_SCROLLLOCK,
    PAUSE = SDLK_PAUSE,
    INSERT = SDLK_INSERT,
    HOME = SDLK_HOME,
    PAGEUP = SDLK_PAGEUP,
    DELETE = SDLK_DELETE,
    END = SDLK_END,
    PAGEDOWN = SDLK_PAGEDOWN,
    ARROW_RIGHT = SDLK_RIGHT,
    ARROW_LEFT = SDLK_LEFT,
    ARROW_DOWN = SDLK_DOWN,
    ARROW_UP = SDLK_UP,
    NUMLOCKCLEAR = SDLK_NUMLOCKCLEAR,
    KP_DIVIDE = SDLK_KP_DIVIDE,
    KP_MULTIPLY = SDLK_KP_MULTIPLY,
    KP_MINUS = SDLK_KP_MINUS,
    KP_PLUS = SDLK_KP_PLUS,
    KP_ENTER = SDLK_KP_ENTER,

    KP_1 = SDLK_KP_1,
    KP_2 = SDLK_KP_2,
    KP_3 = SDLK_KP_3,
    KP_4 = SDLK_KP_4,
    KP_5 = SDLK_KP_5,
    KP_6 = SDLK_KP_6,
    KP_7 = SDLK_KP_7,
    KP_8 = SDLK_KP_8,
    KP_9 = SDLK_KP_9,
    KP_0 = SDLK_KP_0,

    KP_PERIOD = SDLK_KP_PERIOD,
    _KEYSYM_TOTAL,
};

class EventHandler
{
public:
    virtual void handleEvent(const SDL_Event &event) = 0;
    virtual ~EventHandler() = default;
};

class KeyHandler : public EventHandler
{
public:
    KeyHandler();

    virtual void onKeyDown();
    virtual void onKeyUp();
    int getStatus() const;

    virtual void handleEvent(const SDL_Event &event) override;

protected:
    int pressed;
};

class KeyHandlerSingleDown : public KeyHandler
{
public:
    KeyHandlerSingleDown();
    void handleEvent(const SDL_Event &event) override;
};

class MouseHandler : public EventHandler
{
public:
    void handleEvent(const SDL_Event &event) final;

    virtual void onButtonDown();
    virtual void onButtonUp();
    virtual void onMotion();
    virtual void onWheel();

    pixel_t getMouseX() const;
    pixel_t getMouseY() const;
    pixel_t getMouseXRel() const;
    pixel_t getMouseYRel() const;
    int32_t getWheelX() const;
    int32_t getWheelY() const;
    bool isDouble() const;

private:
    mouseButton _trigger;
    Event _event;
};
} // namespace ample::control
