#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <string>

#include "Debug.h"
#include "Exception.h"
#include "SDLEnvironment.h"
#include "Window.h"

namespace ample::window
{
Window::Window(const std::string &name,
               const pixel_t &x,
               const pixel_t &y,
               const pixel_t &width,
               const pixel_t &height,
               const uint32_t &posFlags,
               const uint32_t &modeFlags)
    : _window(name, x, y, width, height, posFlags, modeFlags),
      _glContext(_window.pointer()),
      _width(width), _height(height)
{
    DEBUG(glGetString(GL_VERSION));
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        exception::SDLException::handle();
    }
}

void Window::swapBuffer() noexcept
{
    SDL_GL_SwapWindow(_window.pointer());
}

pixel_t Window::getHeight() const noexcept
{
    return _height;
}

pixel_t Window::getWidth() const noexcept
{
    return _width;
}

void Window::disableCursor() noexcept
{
    SDL_ShowCursor(SDL_DISABLE);
}

void Window::enableCursor() noexcept
{
    SDL_ShowCursor(SDL_ENABLE);
}
void Window::moveCursor(pixel_t x, pixel_t y) noexcept
{
    SDL_WarpMouseInWindow(_window.pointer(), x, y);
}

void Window::resize(pixel_t w, pixel_t h) noexcept
{
    _width = w;
    _height = h;
}

SDL_Window *Window::pointer() noexcept
{
    return _window.pointer();
}

SDL_GLContext *ample::window::Window::glContext() noexcept
{
    return _glContext.pointer();
}
} // namespace ample::window
