#include <SDL2/SDL.h>
#include <iostream>

#include "Window.h"

namespace window
{
Window::Window(const int &width,
               const int &height,
               const char *name,
               const int &flags)
    : width(width), height(height), name(name), flags(flags)
{
    std::cerr << "Init window" << ' ' << name << std::endl;
}

void Window::open()
{
    if (this->windowsCount() == 0)
    {
        this->initSDL();
    }
    windowsCount()++;
    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    std::cerr << "Open window" << ' ' << this->name << std::endl;
}

void Window::close()
{
    windowsCount()--;
    SDL_DestroyWindow(this->window);
    if (this->windowsCount() == 0)
    {
        this->quitSDL();
    }
    std::cerr << "Close window" << ' ' << this->name << std::endl;
}

Window::~Window()
{
    std::cerr << "Delete window" << ' ' << this->name << std::endl;
    return;
}

void Window::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
    std::cerr << "Init SDL" << std::endl;
}

void Window::quitSDL()
{
    SDL_Quit();
    std::cerr << "Quit SDL" << std::endl;
}

int &Window::windowsCount()
{
    static int windowsCounter(0);
    return windowsCounter;
}
} // namespace window
