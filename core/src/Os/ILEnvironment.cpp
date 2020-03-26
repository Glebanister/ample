#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "ILEnvironment.h"
#include "Exception.h"
#include "Debug.h"
#include "OpenGLEnvironment.h"

namespace ample::os::environment
{
ILEnvironment::ILEnvironment()
{
    DEBUG("Setting up IL environment");
    os::environment::OpenGLEnvironment::instance();
    ilInit();
    iluInit();
    exception::DevILException::handle();
    DEBUG("IL environment done");
}

ILEnvironment::~ILEnvironment()
{
    DEBUG("Quit IL environment");
}
} // namespace ample::os::environment
