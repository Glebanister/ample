#include <GL/gl.h>
#include <stdexcept>
#include <cassert>
#include <iostream>

#include "OsManager.h"
#include "Window.h"
#include "Error.h"

namespace os
{
Window::Window(const std::string &name,
               const size_t &x,
               const size_t &y,
               const size_t &width,
               const size_t &height,
               const uint32_t &posFlags,
               const uint32_t &modeFlags)
    : _winPtr(nullptr),
      _manager(new OsManager),
      _name(name),
      _x(x), _y(y),
      _width(width), _height(height),
      _modeFlags(modeFlags),
      _glContext(nullptr),
      _contextX(0), _contextY(0),
      _contextW(width), _contextH(height)
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
}

void Window::setGlViewport(const size_t x, const size_t y, const size_t w, const size_t h)
{
    glViewport(x, y, w, h);
}

void Window::open()
{
    setGlViewport(_contextX, _contextY, _contextW, _contextH);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    _winPtr = OsManager::createWindow(_name.c_str(),
                                      _x, _y,
                                      _width, _height,
                                      _modeFlags);

    _glContext = SDL_GL_CreateContext(_winPtr);
}

void Window::swapBuffer()
{
    if (!_winPtr)
    {
        throw exception::Exception(exception::exId::WINDOW_NOT_READY,
                                   exception::exType::CRITICAL);
    }
    SDL_GL_SwapWindow(_winPtr);
}

size_t Window::getHeight()
{
    return _height;
}

size_t Window::getWidth()
{
    return _width;
}

void Window::resize(const size_t w, const size_t &h)
{
    _width = w;
    _height = h;
    setGlViewport(0, 0, _width, _height);
}

void Window::close()
{
    if (!_winPtr)
    {
        throw exception::Exception(exception::exId::WINDOW_NOT_READY,
                                   exception::exType::CRITICAL);
    }
    SDL_DestroyWindow(_winPtr);
    SDL_GL_DeleteContext(_glContext);
}

Window::~Window()
{
    delete _manager;
}
} // namespace os
