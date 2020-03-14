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
    static ShaderProcessor &instance();

    void addShader(shaderType shaderType, const std::string &shaderPath);
    GLuint getProgramId() const;
    void link();
    void use();
    GLint getUniformLocation(const std::string &name);

private:
    ShaderProcessor();
    ~ShaderProcessor();
    std::unordered_map<std::string, bool> _hasShader;
    std::vector<std::unique_ptr<Shader>> _shaders;
    GLuint _programId;
};
} // namespace ample::graphics::shaders
