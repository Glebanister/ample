#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <SDL/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "VertexShader.h"
#include "Exception.h"

namespace ample::graphics
{
VertexShader::VertexShader(const std::string &filename)
{
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (!vertexShaderId)
    {
        throw exception::Exception(exception::exId::OPENGL_SHADER,
                                   exception::exType::CASUAL,
                                   SDL_GetError());
    }

    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(filename);
    if (!vertexShaderStream.good())
    {
        throw exception::Exception(exception::exId::FILE_READ,
                                   exception::exType::CASUAL);
    }
    {
        std::stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        if (!sstr.good() || !vertexShaderStream.good())
        {
            throw exception::Exception(exception::exId::FILE_READ,
                                       exception::exType::CASUAL);
        }
        vertexShaderCode = sstr.str();
    }

    // Compile Vertex Shader
    {
        char const *vertexSourcePointer = vertexShaderCode.c_str();
        glShaderSource(vertexShaderId, 1, &vertexSourcePointer, NULL);
        glCompileShader(vertexShaderId);
        if (glGetError() != GL_NO_ERROR)
        {
            throw exception::Exception(exception::exId::OPENGL_SHADER,
                                       exception::exType::CASUAL,
                                       SDL_GetError());
        }
    }

    // Check Vertex Shader
    {
        GLint checkResult = GL_FALSE, infoLogLength;
        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &checkResult);
        glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            std::string vertexShaderErrorMessage;
            vertexShaderErrorMessage.resize(infoLogLength);
            glGetShaderInfoLog(vertexShaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
            throw exception::Exception(exception::exId::OPENGL_SHADER,
                                       exception::exType::CASUAL,
                                       vertexShaderErrorMessage);
        }
    }

    // Link the program
    {
        _programId = glCreateProgram();
        glAttachShader(_programId, vertexShaderId);
        glLinkProgram(_programId);
    }

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);

    glDeleteShader(VertexShaderID);
} // namespace ample::graphics
