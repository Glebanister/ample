#include <SDL2/SDL.h>

#include "Window.h"

namespace window
{
Window::Window(const int &width,
               const int &height,
               const char *name,
               const int &flags)
    : width(width), height(height), name(name), flags(flags)
{
}

void Window::open()
{
    windowsCount()++;
    if (this->windowsCount() == 0)
    {
        this->initSDL();
    }
    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
}

void Window::close()
{
    windowsCount()--;
    SDL_DestroyWindow(this->window);
    if (this->windowsCount() == 0)
    {
        this->quitSDL();
    }
}

Window::~Window()
{
    this->close();
}

void Window::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

void Window::quitSDL()
{
    SDL_Quit();
}

int &Window::windowsCount()
{
    static int windowsCounter(0);
    return windowsCounter;
}
} // namespace window
