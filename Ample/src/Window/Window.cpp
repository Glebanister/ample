#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <iostream>
#include <stdexcept>

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
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_LogError(0, "Error initialization SDL %s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("Init SDL\n");

    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_LogError(0, "%s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
        return;
    }
    SDL_Log("Open window %s\n", this->name);

    glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        SDL_LogError(0, "%s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
        return;
    }
    SDL_Log("Create glContext %s\n", this->name);
}

void Window::close()
{
    SDL_DestroyWindow(this->window);
    SDL_GL_DeleteContext(this->glContext);
    SDL_Log("Close window %s\n", this->name);
    SDL_Quit();
    SDL_Log("Quit SDL\n");
}

void Window::refresh()
{
    SDL_GL_SwapWindow(window);
}

Window::~Window()
{
    SDL_Log("Delete window %s\n", this->name);
}
} // namespace window
