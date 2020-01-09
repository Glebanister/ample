#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "Logger.h"

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

enum errOs
{
    ERR_OS_NO,
    ERR_WINDOW_OPENING,
    ERR_SDL_INITIALIZING,
    ERR_OPENGL_CONTEXT,
};

static const char *errOsMessage[] = {
    "Success\n",
    "Can not open window\n",
    "Can not initialize SDL\n",
    "Can not initialize OpenGL context\n",
};

} // namespace os
