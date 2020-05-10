#pragma once

#include <GL/gl.h>

#include "ShaderProcessor.h"
#include "Singleton.h"
#include "Color.h"

namespace ample::graphics::shaders
{
class ShaderProcessor;
} // namespace ample::graphics::shaders

namespace ample::os::environment
{
class OpenGLEnvironment : public utils::Singleton<OpenGLEnvironment>
{
public:
    void setColor(const graphics::Color &color);
    graphics::Color getColor() const noexcept;

protected:
    OpenGLEnvironment();
    ~OpenGLEnvironment();

    GLuint _vertexArrayId;
    graphics::Color _fillColor = {50, 50, 50};
};
} // namespace ample::os::environment
