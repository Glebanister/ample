#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "LightSource.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics::light
{
LightSource::LightSource(const Color ambient,
                         const Color diffuse,
                         const Color specular)
    : _ambient(ambient.r, ambient.g, ambient.b, ambient.a),
      _diffuse(diffuse.r, diffuse.g, diffuse.b, diffuse.a),
      _specular(specular.r, specular.g, specular.b, specular.a),
      _lightVectorId(glGetUniformLocation(shaders::ShaderProcessor::instance().getProgramId(), "light_position"))
{
    static uint8_t globalColorIndex = 0;
    _index = globalColorIndex++;
}

LightSource::LightSource()
    : LightSource(Color{}, Color{}, Color{}) {}

void LightSource::draw(glm::mat4 rotated,
                       glm::mat4 translated)
{
    GraphicalObject::onActive();
    glm::vec3 lightPos{100, 100, 0};
    glUniform3fv(_lightVectorId, 1, &lightPos[0]);
    exception::OpenGLException::handle();
}
} // namespace ample::graphics::light
