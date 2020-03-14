#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Singleton.h"
#include "Noncopyable.h"
#include "OpenGLEnvironment.h"

namespace ample::os::environment
{
class OpenGLEnvironment;
}

namespace ample::graphics::shaders
{
class ShaderProcessor : public utils::Singleton<ShaderProcessor>
{
public:
    enum class UniformType
    {
        MAT4,
        MAT3,
        VEC4,
        VEC3,
    };

    struct Uniform
    {
    private:
        Uniform(float *, const std::string &);
    
    public:    
        Uniform(glm::mat4 &, const std::string &);
        Uniform(glm::mat3 &, const std::string &);
        Uniform(glm::vec4 &, const std::string &);
        Uniform(glm::vec3 &, const std::string &);
        void load();

        float *pointer;
        UniformType type;
        GLint location;
        std::string _name;
    };

public:
    void addShader(shaderType shaderType, const std::string &shaderPath);
    GLuint getProgramId() const;
    GLint getUniformLocation(const std::string &name);
    void link();
    void use();

protected:
    ShaderProcessor();
    ~ShaderProcessor();
    std::unordered_map<std::string, bool> _hasShader;
    std::vector<std::unique_ptr<Shader>> _shaders;
    GLuint _programId;
    std::vector<Uniform> _uniforms;
};
} // namespace ample::graphics::shaders
