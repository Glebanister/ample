#pragma once

#include "Shader.h"

namespace ample::graphics::shaders
{
class FragmentShader final : public Shader
{
public:
    explicit FragmentShader(const std::string &filename, GLuint programId);
    ~FragmentShader();
};
}