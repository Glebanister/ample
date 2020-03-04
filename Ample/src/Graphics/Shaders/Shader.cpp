#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "Debug.h"
#include "Exception.h"

namespace ample::graphics::shaders
{

Shader::Shader(GLuint programId, shaderType shaderType, const std::string &shaderPath)
    : _programId(programId)
{
    DEBUG("Uploading shader from" + shaderPath);
    GLenum
        _shaderId = glCreateShader(shaderByType[shaderType]);
    exception::OpenGLException::handle();

    std::string shaderCode;
    std::ifstream shaderStream(shaderPath);
    if (!shaderStream.good())
    {
        throw exception::Exception(exception::exId::FILE_READ,
                                   exception::exType::CASUAL);
    }
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        if (!sstr.good() || !shaderStream.good())
        {
            throw exception::Exception(exception::exId::FILE_READ,
                                       exception::exType::CASUAL);
        }
        shaderCode = sstr.str();
    }

    DEBUG("Compiling shader");
    {
        char const *sourcePointer = shaderCode.c_str();
        glShaderSource(_shaderId, 1, &sourcePointer, NULL);
        glCompileShader(_shaderId);
        exception::OpenGLException::handle();
    }

    DEBUG("Checking shader");
    {
        GLint checkResult = GL_FALSE, infoLogLength;
        glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &checkResult);
        glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            std::string shaderErrorMessage;
            shaderErrorMessage.resize(infoLogLength);
            glGetShaderInfoLog(_shaderId, infoLogLength, NULL, &shaderErrorMessage[0]);
            exception::OpenGLException::handle(shaderErrorMessage);
        }
    }
    glAttachShader(_programId, _shaderId);
}

Shader::~Shader()
{
    DEBUG("Shader dtor");
    glDetachShader(_programId, _shaderId);
    glDeleteShader(_shaderId);
}
} // namespace ample::graphics::shaders
