#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>

#include "ShaderProcessor.h"
#include "Debug.h"
#include "Exception.h"
#include "VertexShader.h"
#include "FragmentShader.h"

namespace ample::graphics::shaders
{
ShaderProcessor::ShaderProcessor()
{
    _programId = glCreateProgram();
    exception::OpenGLException::handle();
}

void ShaderProcessor::addShader(shaderType shaderType, const std::string &shaderPath)
{
    if (_hasShader[shaderPath])
    {
        return;
    }
    _hasShader[shaderPath] = true;
    switch (shaderType)
    {
    case shaderType::VERTEX:
        _shaders.push_back(std::make_unique<VertexShader>(shaderPath, _programId));
        break;
    case shaderType::FRAGMENT:
        _shaders.push_back(std::make_unique<FragmentShader>(shaderPath, _programId));
        break;
    default:
        DEBUG("Uknown shader");
    }
}

void ShaderProcessor::link()
{
    DEBUG("Linking shaders");
    glLinkProgram(_programId);
    exception::OpenGLException::handle();

    DEBUG("Checking shaders");

    GLint result = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(_programId, GL_LINK_STATUS, &result);
    glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength)
    {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(_programId, infoLogLength, NULL, &programErrorMessage[0]);
        std::string message = "";
        for (auto c : programErrorMessage)
        {
            message += c;
        }
        DEBUG(message);
        exception::OpenGLException::handle(message.c_str());
    }
    glValidateProgram(_programId);
    exception::OpenGLException::handle();

    glUseProgram(_programId);
    exception::OpenGLException::handle();

    DEBUG("Shaders - done!");
}
} // namespace ample::graphics::shaders
