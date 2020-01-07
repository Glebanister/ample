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
    SDL_Log("Init window %s\n", name);
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
    SDL_Log("Open window %s\n", this->name);
}

void Window::close()
{
    windowsCount()--;
    SDL_DestroyWindow(this->window);
    if (this->windowsCount() == 0)
    {
        this->quitSDL();
    }
    SDL_Log("Close window %s\n", this->name);
}

Window::~Window()
{
    SDL_Log("Delete window %s\n", this->name);
    return;
}

void Window::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_LogError(0, "Error initialization SDL %s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    SDL_Log("Init SDL\n");
}

void Window::quitSDL()
{
    SDL_Quit();
    SDL_Log("Quit SDL\n");
}

int &Window::windowsCount()
{
    static int windowsCounter(0);
    return windowsCounter;
}
} // namespace window
