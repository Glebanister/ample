#define GL_GLEXT_PROTOTYPES 1
#define GLM_ENABLE_EXPERIMENTAL

#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProcessor.h"
#include "Debug.h"
#include "Exception.h"
#include "Shader.h"
#include "OpenGLEnvironment.h"

namespace ample::graphics::shaders
{
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

GLint ShaderProcessor::getUniformLocation(const std::string &name)
{
    return glGetUniformLocation(_programId, name.c_str());
}

ShaderProcessor::~ShaderProcessor()
{
    DEBUG("Destroy shader processor");
    glDeleteProgram(_programId);
}

ShaderProcessor::Uniform::Uniform(float *data, const std::string &name)
    : pointer(data),
      location(glGetUniformLocation(ShaderProcessor::instance().getProgramId(), name.c_str())),
      _name(name)
{
    if (location < 0)
    {
        throw exception::Exception(exception::exId::OPENGL,
                                   exception::exType::CRITICAL,
                                   "could not find uniform '" + name + "'");
    }
    ASSERT(pointer);
}

ShaderProcessor::Uniform::Uniform(glm::mat4 &data, const std::string &name)
    : Uniform(glm::value_ptr(data), name)
{
    type = UniformType::MAT4;
}
ShaderProcessor::Uniform::Uniform(glm::mat3 &data, const std::string &name)
    : Uniform(glm::value_ptr(data), name)
{
    type = UniformType::MAT3;
}
ShaderProcessor::Uniform::Uniform(glm::vec4 &data, const std::string &name)
    : Uniform(glm::value_ptr(data), name)
{
    type = UniformType::VEC4;
}
ShaderProcessor::Uniform::Uniform(glm::vec3 &data, const std::string &name)
    : Uniform(glm::value_ptr(data), name)
{
    type = UniformType::VEC3;
}

void ShaderProcessor::Uniform::load()
{
    ASSERT(_name.length() != 0);
    if (!pointer)
    {
        throw exception::Exception(exception::exId::OPENGL,
                                   exception::exType::CRITICAL,
                                   "uniform pointer is null" + _name);
    }
    switch (type)
    {
    case UniformType::MAT4:
        glUniformMatrix4fv(location, 1, GL_FALSE, pointer);
        break;
    case UniformType::MAT3:
        glUniformMatrix3fv(location, 1, GL_FALSE, pointer);
        break;
    case UniformType::VEC4:
        glUniform4fv(location, 1, pointer);
        break;
    case UniformType::VEC3:
        glUniform3fv(location, 1, pointer);
        break;
    }
    exception::OpenGLException::handle();
}
} // namespace ample::graphics::shaders
