#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <iostream>
#include <stdexcept>

#include "Window.h"
#include "Logger.h"

namespace window
{
Window::Window(const int &width,
               const int &height,
               const char *name,
               const int &flags)
    : width(width), height(height), name(name), flags(flags)
{
    os::Logger::logInfo("Init window %s\n", this->name);
}

void Window::open()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        os::Logger::logCritical("Error initialization SDL %s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }
    os::Logger::logInfo("Init SDL\n");

    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        os::Logger::logCritical("%s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
        return;
    }
    os::Logger::logInfo("Open window %s\n", this->name);

    glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        os::Logger::logCritical("%s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
        return;
    }
    os::Logger::logInfo("Create glContext %s\n", this->name);
}

void Window::close()
{
    SDL_DestroyWindow(this->window);
    SDL_GL_DeleteContext(this->glContext);
    os::Logger::logInfo("Close window %s\n", this->name);
    SDL_Quit();
    os::Logger::logInfo("Quit SDL\n");
}

void Window::refresh()
{
    SDL_GL_SwapWindow(window);
}

Window::~Window()
{
    os::Logger::logInfo("Delete window %s\n", this->name);
}
} // namespace window
