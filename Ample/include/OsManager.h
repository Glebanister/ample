#pragma once

#include "Logger.h"

namespace os
{
static bool __sdl_was_init(false);

class OsManager final
{
public:
    OsManager(bool log=true);
    void initSDLOnce();
private:
    
    Logger *log;
};
}
