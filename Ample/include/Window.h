#pragma once

#include <SDL2/SDL.h>
#include <stdexcept>

namespace window
{

enum mode
{
    NORMAL = 0,
    FULLSCREEN = SDL_WINDOW_FULLSCREEN,
    BORDERLESS = SDL_WINDOW_BORDERLESS,
    RESIZABLE = SDL_WINDOW_RESIZABLE,
    MAXIMIZED = SDL_WINDOW_MAXIMIZED,
    MINIMIZED = SDL_WINDOW_MINIMIZED,
};

class Window
{
public:
    Window() = delete;
    Window(const int &width,
           const int &height,
           const char *name,
           const int &flags);

    void open();
    void close();

    void refresh();

    Window(const Window &other) = delete;
    Window &operator=(const Window &other) = delete;

    ~Window();

protected:
    SDL_Window *window;
    SDL_GLContext glContext;
    int width, height;
    const char *name;
    int flags;
};
} // namespace window
