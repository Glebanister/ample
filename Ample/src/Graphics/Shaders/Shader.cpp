#include "Shader.h"

namespace ample::graphics::shaders
{
Shader::Shader(GLuint programId)
    : _programId(programId) {}

GLuint Shader::getShaderId() const
{
    return _shaderId;
}
} // namespace ample::graphics::shaders
