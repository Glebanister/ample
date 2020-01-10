#include <SDL2/SDL.h>
#include <stdexcept>
#include <cassert>

#include "OsManager.h"
#include "Window.h"

namespace os
{
Window::Window(const char *name,
               const int &x,
               const int &y,
               const int &width,
               const int &height,
               const int &posFlags,
               const int &modeFlags)
    : name(name),
      x(x), y(y),
      width(width), height(height),
      modeFlags(modeFlags)
{
    this->manager = new OsManager();
    if (modeFlags & winpos::CENTERED_X)
    {
        this->x = SDL_WINDOWPOS_CENTERED;
    }
    if (modeFlags & winpos::CENTERED_Y)
    {
        this->y = SDL_WINDOWPOS_CENTERED;
    }
    if (modeFlags & winpos::UNDEFINED_POS)
    {
        this->x = SDL_WINDOWPOS_UNDEFINED;
        this->y = SDL_WINDOWPOS_UNDEFINED;
    }
}

void Window::open()
{
    if ((this->winPtr = OsManager::createWindow(this->name,
                                                this->x, this->y,
                                                this->width, this->height,
                                                this->modeFlags)) == nullptr)
    {
        throw std::runtime_error(errOsMessage[errOs::ERR_WINDOW_OPENING]);
    }

    Logger::logInfo("Window %s opened\n", this->name);
    assert(this->winPtr);
    if (!(this->glContext = SDL_GL_CreateContext(this->winPtr)))
    {
        Logger::logCritical("Can not create OpenGL context: %s\n", SDL_GetError());
        throw std::runtime_error(errOsMessage[errOs::ERR_OPENGL_CONTEXT]);
    }
    else
    {
        Logger::logInfo("OpenGL context created for %s\n", this->name);
    }
}

void Window::refresh()
{
    SDL_GL_SwapWindow(this->winPtr);
}

void Window::close()
{
    assert(this->winPtr);
    SDL_DestroyWindow(this->winPtr);
    Logger::logInfo("Window %s destroyed\n", this->name);
    SDL_GL_DeleteContext(this->glContext);
    Logger::logInfo("OpenGL context %s deleted\n", this->name);
}

Window::~Window()
{
    delete this->manager;
}
} // namespace os
