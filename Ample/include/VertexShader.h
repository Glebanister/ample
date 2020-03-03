#pragma once

#include <string>

#include "Shader.h"

namespace ample::graphics::shaders
{
class VertexShader final : public Shader
{
public:
    explicit VertexShader(const std::string &filename, GLuint programId);
    ~VertexShader();
};
} // namespace ample::graphics::shaders
