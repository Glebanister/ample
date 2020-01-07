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
    if (this->windowsCount() == 0)
    {
        this->initSDL();
    }
    windowsCount()++;
}

void Window::open()
{
    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
}

Window::~Window()
{
    windowsCount()--;
    if (windowsCount() == 0)
    {
        this->quitSDL();
    }
    SDL_DestroyWindow(this->window);
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
