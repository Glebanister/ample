#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "LightSource.h"
#include "Exception.h"
#include "ShaderProcessor.h"
#include "Debug.h"

namespace ample::graphics::light
{
LightSource::LightSource(const Color ambient,
                         const Color diffuse,
                         const Color specular)
    : _ambient(ambient.r, ambient.g, ambient.b, ambient.a),
      _diffuse(diffuse.r, diffuse.g, diffuse.b, diffuse.a),
      _specular(specular.r, specular.g, specular.b, specular.a),
      _lightVectorUniform(std::make_unique<shaders::ShaderProcessor::Uniform>(_position, "light_position"))
{
}

LightSource::LightSource()
    : LightSource(Color{}, Color{}, Color{}) {}

void LightSource::drawSelf()
{
    _position = _modelMatrix * glm::vec4{1.0f};
    _lightVectorUniform->load();
}
} // namespace ample::graphics::light
