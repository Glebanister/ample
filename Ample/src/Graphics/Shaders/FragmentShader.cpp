#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <SDL/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "FragmentShader.h"
#include "Exception.h"
#include "Debug.h"
#include "Utils.h"

namespace ample::graphics::shaders
{
FragmentShader::FragmentShader(const std::string &filename, GLuint programId)
    : Shader(programId)
{
    DEBUG("Uploading fragment shader from" + filename);
    _shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    exception::OpenGLException::handle();

    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(filename);
    if (!FragmentShaderStream.good())
    {
        throw exception::Exception(exception::exId::FILE_READ,
                                   exception::exType::CASUAL);
    }
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        if (!sstr.good() || !FragmentShaderStream.good())
        {
            throw exception::Exception(exception::exId::FILE_READ,
                                       exception::exType::CASUAL);
        }
        FragmentShaderCode = sstr.str();
    }

    DEBUG("Compiling fragment shader " + filename);
    {
        char const *fragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(_shaderId, 1, &fragmentSourcePointer, NULL);
        glCompileShader(_shaderId);
        exception::OpenGLException::handle();
    }

    // Check fragment Shader
    {
        GLint checkResult = GL_FALSE, infoLogLength;
        glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &checkResult);
        glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            std::string FragmentShaderErrorMessage;
            FragmentShaderErrorMessage.resize(infoLogLength);
            glGetShaderInfoLog(_shaderId, infoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            exception::OpenGLException::handle(FragmentShaderErrorMessage);
        }
    }
    glAttachShader(_programId, _shaderId);
}

FragmentShader::~FragmentShader()
{
    glDetachShader(_programId, _shaderId);
    glDeleteShader(_shaderId);
}
} // namespace ample::graphics::shaders
