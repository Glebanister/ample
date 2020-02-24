#include <string>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "Window.h"
#include "Exception.h"

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

    if (!SDL_WasInit(SDL_INIT_EVERYTHING))
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            throw exception::Exception(
                exception::exId::SDL_INIT,
                exception::exType::CRITICAL,
                SDL_GetError());
        }
    }
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    _winPtr = SDL_CreateWindow(_name.c_str(), _x, _y,
                               _width, _height,
                               _modeFlags | SDL_WINDOW_OPENGL);
    if (!_winPtr)
    {
        SDL_Quit();
        throw exception::Exception(
            exception::exId::WINDOW_OPEN,
            exception::exType::CRITICAL,
            SDL_GetError());
    }
    _glContext = SDL_GL_CreateContext(_winPtr);
    if (!_glContext)
    {
        SDL_DestroyWindow(_winPtr);
        SDL_Quit();
        throw exception::Exception(
            exception::exId::OPENGL_INIT,
            exception::exType::CRITICAL,
            SDL_GetError());
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT | GL_BACK, GL_FILL);
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
    SDL_Quit();
}
} // namespace ample::window
