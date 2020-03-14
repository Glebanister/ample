#include <string>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "Window.h"
#include "Exception.h"
#include "SDLEnvironment.h"
#include "Debug.h"

namespace ample::window
{
Window::Window(const std::string &name,
               const pixel_t &x,
               const pixel_t &y,
               const pixel_t &width,
               const pixel_t &height,
               const uint32_t &posFlags,
               const uint32_t &modeFlags)
    : _winPtr(nullptr),
      _name(name),
      _x(x), _y(y),
      _width(width), _height(height),
      _modeFlags(modeFlags),
      _glContext(nullptr)
{
    if (posFlags & winpos::CENTERED_X)
    {
        _x = SDL_WINDOWPOS_CENTERED;
    }
    if (posFlags & winpos::CENTERED_Y)
    {
        _y = SDL_WINDOWPOS_CENTERED;
    }
    if (posFlags & winpos::UNDEFINED_POS)
    {
        _x = SDL_WINDOWPOS_UNDEFINED;
        _y = SDL_WINDOWPOS_UNDEFINED;
    }

    os::environment::SDLEnvironment::instance();

    _winPtr = SDL_CreateWindow(_name.c_str(), _x, _y,
                               _width, _height,
                               _modeFlags | SDL_WINDOW_OPENGL);
    if (!_winPtr)
    {
        SDL_Quit();
        exception::SDLException::handle();
    }
    _glContext = SDL_GL_CreateContext(_winPtr);
    if (!_glContext)
    {
        SDL_DestroyWindow(_winPtr);
        SDL_Quit();
        exception::OpenGLException::handle();
    }
    DEBUG(glGetString(GL_VERSION));
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        SDL_DestroyWindow(_winPtr);
        SDL_Quit();
        exception::SDLException::handle();
    }
}

void Window::swapBuffer()
{
    SDL_GL_SwapWindow(_winPtr);
}

pixel_t Window::getHeight() const
{
    return _height;
}

pixel_t Window::getWidth() const
{
    return _width;
}

void Window::disableCursor() const
{
    SDL_ShowCursor(SDL_DISABLE);
}
void Window::enableCursor() const
{
    SDL_ShowCursor(SDL_ENABLE);
}
void Window::moveCursor(pixel_t x, pixel_t y) const
{
    SDL_WarpMouseInWindow(_winPtr, x + getWidth() / 2, -y + getHeight() / 2);
}

void Window::resize(const pixel_t w, const pixel_t &h)
{
    _width = w;
    _height = h;
}

Window::~Window()
{
    SDL_DestroyWindow(_winPtr);
    SDL_GL_DeleteContext(_glContext);
}
} // namespace ample::window
