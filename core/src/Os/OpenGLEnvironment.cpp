#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>

#include "Debug.h"
#include "Exception.h"
#include "OpenGLEnvironment.h"
#include "SDLEnvironment.h"
#include "ShaderProcessor.h"

namespace ample::os::environment
{
OpenGLEnvironment::OpenGLEnvironment()
{
    DEBUG("Setting up opengl environment");
    SDLEnvironment::instance();
    graphics::shaders::ShaderProcessor::instance().addShader(ample::graphics::shaders::shaderType::VERTEX,
                                                             "core/src/Graphics/Shaders/Shaders/BasicVertexShader.vert");
    graphics::shaders::ShaderProcessor::instance().addShader(ample::graphics::shaders::shaderType::FRAGMENT,
                                                             "core/src/Graphics/Shaders/Shaders/BasicFragmentShader.frag");
    graphics::shaders::ShaderProcessor::instance().link();
    graphics::shaders::ShaderProcessor::instance().use();

    glGenVertexArrays(1, &_vertexArrayId);
    glBindVertexArray(_vertexArrayId);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    exception::OpenGLException::handle();
    DEBUG("Opengl environment done!");
}

void OpenGLEnvironment::setColor(const graphics::Color &color)
{
    _fillColor = color;
}

graphics::Color OpenGLEnvironment::getColor() const noexcept
{
    return _fillColor;
}

OpenGLEnvironment::~OpenGLEnvironment()
{
    glDeleteVertexArrays(1, &_vertexArrayId);
    DEBUG("Quit from opengl context");
}
} // namespace ample::os::environment
