#pragma once

#include "Singleton.h"

namespace ample::os::environment
{
class SDLEnvironment : public utils::Singleton<SDLEnvironment>
{
protected:
    SDLEnvironment();
    ~SDLEnvironment();
};
} // namespace ample::os::environment
