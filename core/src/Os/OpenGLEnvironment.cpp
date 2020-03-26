#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>

#include "OpenGLEnvironment.h"
#include "Exception.h"
#include "ShaderProcessor.h"
#include "Debug.h"
#include "SDLEnvironment.h"

namespace ample::os::environment
{
OpenGLEnvironment::OpenGLEnvironment()
{
    DEBUG("Setting up opengl environment");
    SDLEnvironment::instance();
    graphics::shaders::ShaderProcessor::instance().addShader(ample::graphics::shaders::shaderType::VERTEX,
                                                             "../../core/src/Graphics/Shaders/Shaders/BasicVertexShader.vert");
    graphics::shaders::ShaderProcessor::instance().addShader(ample::graphics::shaders::shaderType::FRAGMENT,
                                                             "../../core/src/Graphics/Shaders/Shaders/BasicFragmentShader.frag");
    graphics::shaders::ShaderProcessor::instance().link();
    graphics::shaders::ShaderProcessor::instance().use();

    glClearColor(50.0 / 256.0, 50.0 / 256.0, 50.0 / 256.0, 0.5);
    glGenVertexArrays(1, &_vertexArrayId);
    glBindVertexArray(_vertexArrayId);
    glEnable(GL_DEPTH_TEST);
    exception::OpenGLException::handle();
    DEBUG("Opengl environment done!");
}

OpenGLEnvironment::~OpenGLEnvironment()
{
    glDeleteVertexArrays(1, &_vertexArrayId);
    DEBUG("Quit from opengl context");
}
} // namespace ample::os::environment
