#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#include "LightSource.h"
#include "Exception.h"
#include "ShaderProcessor.h"
#include "Debug.h"

namespace ample::graphics::light
{
LightSource::LightSource(const std::string &name)
    : GraphicalObject(name),
      _lightPositionUnirom(_position, "light.position"),
      _lightIntensitiesUniform(_intensities, "light.intensities")
{
}

void LightSource::addIntensitiy(const Color &color)
{
    _intensities += glm::vec3{color.r, color.g, color.b};
    _intensities[0] = std::max(_intensities[0], 0.0f);
    _intensities[1] = std::max(_intensities[1], 0.0f);
    _intensities[2] = std::max(_intensities[2], 0.0f);
    _intensities[0] = std::min(_intensities[0], 1.0f);
    _intensities[1] = std::min(_intensities[1], 1.0f);
    _intensities[2] = std::min(_intensities[2], 1.0f);
}

void LightSource::drawSelf()
{
    auto position4 = _modelMatrix * glm::vec4{1.0f};
    _position = {position4.x, position4.y, position4.z};
    _lightPositionUnirom.load();
    _lightIntensitiesUniform.load();
}
} // namespace ample::graphics::light
