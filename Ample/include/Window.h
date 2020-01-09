#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "Logger.h"

namespace os
{
class OsManager;

class Window final
{
public:
    Window(const char *name,
           const int &x,
           const int &y,
           const int &width,
           const int &height,
           const int &posFlags,
           const int &modeFlags);

    Window() = delete;
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    void open();
    void close();

    void refresh();

    ~Window();

private:
    SDL_Window *winPtr = nullptr;
    OsManager *manager;
    const char *name;
    int x, y;
    int width, height;
    int modeFlags;
    SDL_GLContext glContext;
};

enum winpos
{
    UNDEFINED = 0b0,
    CENTERED_X = 0b1,
    CENTERED_Y = 0b10,
};

enum winmode
{
    NORMAL = 0,
    FULLSCREEN = SDL_WINDOW_FULLSCREEN,
    BORDERLESS = SDL_WINDOW_BORDERLESS,
    RESIZABLE = SDL_WINDOW_RESIZABLE,
    MAXIMIZED = SDL_WINDOW_MAXIMIZED,
    MINIMIZED = SDL_WINDOW_MINIMIZED,
};

} // namespace os
