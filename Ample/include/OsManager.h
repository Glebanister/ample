#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "Error.h"

namespace os
{

class OsManager final
{
public:
    OsManager();

    OsManager(const OsManager &other) = delete;
    OsManager &operator=(const OsManager &other) = delete;

    static SDL_Window *createWindow(const char *title,
                                    int x, int y,
                                    int w, int h,
                                    uint32_t flags);

    ~OsManager();

private:
    int &numberOfInstances();
};

} // namespace os
