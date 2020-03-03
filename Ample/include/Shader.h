#pragma once

#include <string>
#include <GL/gl.h>

#include "Noncopyable.h"

namespace ample::graphics::shaders
{
class Shader : public utils::Noncopyable
{
public:
    explicit Shader(GLuint programId);
    GLuint getShaderId() const;

protected:
    GLuint _shaderId;
    GLuint _programId;
};
} // namespace ample::graphics::shaders
