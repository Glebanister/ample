#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include "Shader.h"
#include "Singleton.h"
#include "Noncopyable.h"

namespace ample::graphics::shaders
{
class ShaderProcessor final : utils::Noncopyable
{
public:
    ShaderProcessor();
    void addShader(shaderType shaderType, const std::string &shaderPath);
    void link();
    void use();
    ~ShaderProcessor();

private:
    std::unordered_map<std::string, bool> _hasShader;
    std::vector<std::unique_ptr<Shader>> _shaders;
    GLuint _programId;
};
} // namespace ample::graphics::shaders
