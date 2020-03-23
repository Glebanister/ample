#pragma once

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "Singleton.h"

namespace ample::os::environment
{
class ILEnvironment : public utils::Singleton<ILEnvironment>
{
protected:
    ILEnvironment();
    ~ILEnvironment();
};
} // namespace ample::os::environment
