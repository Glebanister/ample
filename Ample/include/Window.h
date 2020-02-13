#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>

#include "OsManager.h"

namespace os
{
enum winpos : uint32_t
{
    UNDEFINED_POS = 0b0,
    CENTERED_X = 0b1,
    CENTERED_Y = 0b10,
};

enum winmode : uint32_t
{
    UNDEFINED_MODE = 0,
    FULLSCREEN = SDL_WINDOW_FULLSCREEN,
    BORDERLESS = SDL_WINDOW_BORDERLESS,
    RESIZABLE = SDL_WINDOW_RESIZABLE,
    MAXIMIZED = SDL_WINDOW_MAXIMIZED,
    MINIMIZED = SDL_WINDOW_MINIMIZED,
};

class OsManager;

class Window final
{
public:
    Window() = delete;

    Window(const std::string &name,
           const size_t &x,
           const size_t &y,
           const size_t &width,
           const size_t &height,
           const uint32_t &posFlags,
           const uint32_t &modeFlags);

    Window(const Window &other) = delete;
    Window &operator=(const Window &) = delete;

    void setGlViewport(const size_t x, const size_t y, const size_t w, const size_t h);

    void open();
    void close();

    void swapBuffer();

    size_t getWidth();
    size_t getHeight();

    void resize(const size_t w, const size_t &h);

    ~Window();

private:
    SDL_Window *_winPtr = nullptr;
    OsManager *_manager = nullptr;
    std::string _name;
    size_t _x, _y;
    size_t _width, _height;
    uint32_t _modeFlags;
    SDL_GLContext _glContext;
    size_t _contextX, _contextY;
    size_t _contextW, _contextH;
};


} // namespace os
