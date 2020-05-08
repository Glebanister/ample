#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace ample::window
{
typedef double pixel_t;

enum winpos : uint32_t
{
    UNDEFINED_POS = 0b0,
    CENTERED_X = 0b1,
    CENTERED_Y = 0b10,
};

enum winmode : uint32_t
{
    UNDEFINED_MODE = 0,
    FULLSCREEN = SDL_WINDOW_FULLSCREEN,
    BORDERLESS = SDL_WINDOW_BORDERLESS,
    RESIZABLE = SDL_WINDOW_RESIZABLE,
    MAXIMIZED = SDL_WINDOW_MAXIMIZED,
    MINIMIZED = SDL_WINDOW_MINIMIZED,
};

class Window final
{
public:
    Window() = delete;

    Window(const std::string &name,
           const pixel_t &x,
           const pixel_t &y,
           const pixel_t &width,
           const pixel_t &height,
           const uint32_t &posFlags,
           const uint32_t &modeFlags);

    void swapBuffer();

    pixel_t getWidth() const;
    pixel_t getHeight() const;

    void disableCursor() const;
    void enableCursor() const;
    void moveCursor(pixel_t x, pixel_t y) const;

    void resize(const pixel_t w, const pixel_t &h);

    SDL_Window *pointer();
    SDL_GLContext *glContext() const noexcept;

    ~Window();

private:
    SDL_Window *_winPtr = nullptr;
    std::string _name;
    pixel_t _x, _y;
    pixel_t _width, _height;
    uint32_t _modeFlags;
    SDL_GLContext *_glContext;
    SDL_GLContext _glContextImpl;
};
} // namespace ample::window
