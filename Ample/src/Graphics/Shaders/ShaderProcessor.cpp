#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>

#include "ShaderProcessor.h"
#include "Debug.h"
#include "Exception.h"
#include "Shader.h"

namespace ample::graphics::shaders
{
ShaderProcessor &ShaderProcessor::instance()
{
    static ShaderProcessor *pInstance = nullptr;
    if (!pInstance)
    {
        pInstance = new ShaderProcessor{};
        DEBUG("Init shader processor");
    }
    return *pInstance;
}

ShaderProcessor::ShaderProcessor()
{
    _programId = glCreateProgram();
    exception::OpenGLException::handle();
}

GLuint ShaderProcessor::getProgramId() const
{
    return _programId;
}

void ShaderProcessor::addShader(shaderType shaderType, const std::string &shaderPath)
{
    if (_hasShader[shaderPath])
    {
        return;
    }
    _hasShader[shaderPath] = true;
    _shaders.push_back(std::make_unique<Shader>(_programId, shaderType, shaderPath));
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

    DEBUG("Shaders - done!");
}

void ShaderProcessor::use()
{
    glUseProgram(_programId);
}

ShaderProcessor::~ShaderProcessor()
{
    DEBUG("Shader processor dtor");
    glDeleteProgram(_programId);
}
} // namespace ample::graphics::shaders
