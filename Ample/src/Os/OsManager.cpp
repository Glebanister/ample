#include <SDL2/SDL.h>
#include <stdexcept>
#include <cassert>

#include "OsManager.h"

namespace os
{
OsManager::OsManager()
{
    if (++numberOfInstances() == 1)
    {
        if (SDL_WasInit(SDL_INIT_EVERYTHING))
        {
            throw exception::Exception(
                exception::exId::SDL_DOUBLE_INIT,
                exception::exType::CRITICAL);
        }
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            throw exception::Exception(
                exception::exId::SDL_INIT,
                exception::exType::CRITICAL);
        }
    }
}

SDL_Window *OsManager::createWindow(const char *title,
                                    int x, int y,
                                    int w, int h,
                                    uint32_t flags)
{
    if (!SDL_WasInit(SDL_INIT_EVERYTHING))
    {
        throw exception::Exception(
            exception::exId::SDL_NOT_READY,
            exception::exType::CRITICAL);
    }
    auto window = SDL_CreateWindow(title, x, y, w, h, flags | SDL_WINDOW_OPENGL);
    if (!window)
    {
        throw exception::Exception(
            exception::exId::WINDOW_OPEN,
            exception::exType::CRITICAL);

        return nullptr;
    }

    return window;
}

int &OsManager::numberOfInstances()
{
    static int count(0);
    return count;
}

OsManager::~OsManager()
{
    if (--numberOfInstances() == 0)
    {
        SDL_Quit();
    }
}
} // namespace os
