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
        assert(!SDL_WasInit(SDL_INIT_EVERYTHING));
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            Logger::logCritical("Can not initialize SDL %s\n", SDL_GetError());
            throw std::runtime_error(errOsMessage[errOs::ERR_SDL_INITIALIZING]);
        }
        else
        {
            Logger::logInfo("SDL initializated\n");
        }
    }
}

SDL_Window *OsManager::createWindow(const char *title,
                                    int x, int y,
                                    int w, int h,
                                    uint32_t flags)
{
    assert(SDL_WasInit(SDL_INIT_EVERYTHING));
    auto window = SDL_CreateWindow(title, x, y, w, h, flags | SDL_WINDOW_OPENGL);
    if (!window)
    {
        Logger::logCritical("Can not create window, %s\n", SDL_GetError());
        return nullptr;
    }
    else
    {
        Logger::logInfo("Window created\n");
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
    assert(SDL_WasInit(SDL_INIT_EVERYTHING));
    if (--numberOfInstances() == 0)
    {
        SDL_Quit();
        Logger::logInfo("SDL quitted\n");
    }
}
} // namespace os
