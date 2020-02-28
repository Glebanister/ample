#pragma once

#include <string>

#include "Shader.h"

namespace ample::graphics
{
class VertexShader : public Shader
{
public:
    explicit VertexShader(const std::string &filename);
};
} // namespace ample::graphics