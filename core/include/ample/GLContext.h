#pragma once

#include <GL/gl.h>
#include <SDL2/SDL.h>

#include "Noncopyable.h"

namespace ample::os
{
class GLContext : public utils::Noncopyable
{
public:
    GLContext(SDL_Window *);
    SDL_GLContext *pointer() noexcept;
    ~GLContext();

private:
    SDL_GLContext _context;
};
} // namespace ample::os
