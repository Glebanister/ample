#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Noncopyable.h"

namespace ample::window
{
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

class SDLWindow : public utils::Noncopyable
{
public:
    SDLWindow(const std::string &title,
              int x,
              int y,
              int w,
              int h,
              uint32_t posFlags,
              uint32_t modeFlags);

    SDL_Window *pointer() noexcept;

    ~SDLWindow();

private:
    SDL_Window *_winPtr = nullptr;
};
} // namespace ample::window
