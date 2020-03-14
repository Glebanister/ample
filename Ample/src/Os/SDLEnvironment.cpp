#include <SDL2/SDL.h>

#include "SDLEnvironment.h"
#include "Exception.h"
#include "Debug.h"

namespace ample::os::environment
{
SDLEnvironment::SDLEnvironment()
{
    DEBUG("Setting up SDL environment");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
    {
        exception::SDLException::handle();
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    DEBUG("SDL environment done");
}

SDLEnvironment::~SDLEnvironment()
{
    SDL_Quit();
    DEBUG("Quit SDL environment");
}
} // namespace ample::os::environment
