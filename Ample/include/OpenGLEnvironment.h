#pragma once

#include <GL/gl.h>

#include "ShaderProcessor.h"
#include "Singleton.h"

namespace ample::graphics::shaders
{
class ShaderProcessor;
} // namespace ample::graphics::shaders

namespace ample::os::environment
{
class OpenGLEnvironment : public utils::Singleton<OpenGLEnvironment>
{
protected:
    OpenGLEnvironment();
    ~OpenGLEnvironment();

    GLuint _vertexArrayId;
};
} // namespace ample::os::environment
