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
    LightSource();

    void drawSelf() override;
    void addIntensitiy(const Color &);

private:
    glm::vec3 _position;
    glm::vec3 _intensities{1.0, 1.0, 1.0};
    shaders::ShaderProcessor::Uniform _lightPositionUnirom;
    shaders::ShaderProcessor::Uniform _lightIntensitiesUniform;
};
} // namespace ample::graphics::light
