#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Color.h"
#include "GraphicalObject.h"
#include "ShaderProcessor.h"

namespace ample::graphics::light
{
class LightSource : public GraphicalObject
{
public:
    LightSource(const Color ambient,
                const Color diffuse,
                const Color specular);
    LightSource();

    void drawSelf(const glm::mat4 &) override;

private:
    float _intensity;
    glm::vec4 _ambient;
    glm::vec4 _diffuse;
    glm::vec4 _specular;
    uint8_t _index;
    std::unique_ptr<shaders::ShaderProcessor::Uniform> _lightVectorUniform;
    glm::vec3 _position;
};
} // namespace ample::graphics::light
