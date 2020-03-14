#pragma once

#include <GL/gl.h>

#include "ShaderProcessor.h"

namespace ample::graphics::shaders
{
class ShaderProcessor;
} // namespace ample::graphics::shaders

namespace ample::os::environment
{
class OpenGLEnvironment final
{
public:
    static OpenGLEnvironment &instance();

private:
    OpenGLEnvironment();
    ~OpenGLEnvironment();

    GLuint _vertexArrayId;
};
} // namespace ample::os::environment
