#pragma once

#include <string>
#include <GL/gl.h>
#include <unordered_map>

#include "Noncopyable.h"

namespace ample::graphics::shaders
{

enum class shaderType
{
    VERTEX,
    FRAGMENT,
};

static std::unordered_map<shaderType, GLint> shaderByType{
    {shaderType::VERTEX, GL_VERTEX_SHADER},
    {shaderType::FRAGMENT, GL_FRAGMENT_SHADER},
};

class Shader final : public utils::Noncopyable
{
public:
    explicit Shader(GLuint programId, shaderType shaderType, const std::string &shaderPath);
    ~Shader();

protected:
    GLuint _shaderId;
    GLuint _programId;
};
} // namespace ample::graphics::shaders
