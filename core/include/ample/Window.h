#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "SDLWindow.h"
#include "GLContext.h"
#include "Noncopyable.h"

namespace ample::window
{
using pixel_t = double;

class Window final : public utils::Noncopyable
{
public:
    Window(const std::string &name,
           const pixel_t &x,
           const pixel_t &y,
           const pixel_t &width,
           const pixel_t &height,
           const uint32_t &posFlags,
           const uint32_t &modeFlags);

    void swapBuffer() noexcept;

    pixel_t getWidth() const noexcept;
    pixel_t getHeight() const noexcept;

    void disableCursor() noexcept;
    void enableCursor() noexcept;
    void moveCursor(pixel_t x, pixel_t y) noexcept;
    void resize(pixel_t w, pixel_t h) noexcept;

    SDL_Window *pointer() noexcept;
    SDL_GLContext *glContext() noexcept;

private:
    SDLWindow _window;
    os::GLContext _glContext;

    pixel_t _x, _y;
    pixel_t _width, _height;
};
} // namespace ample::window
