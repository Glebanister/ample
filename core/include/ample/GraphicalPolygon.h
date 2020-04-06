#pragma once

#include <string>
#include <vector>

#include "GraphicalObject.h"

namespace ample::graphics
{
class GraphicalPolygon : public GraphicalObject
{
public:
    GraphicalPolygon(const std::string &name,
                     const std::vector<Vector2d<float>> &shape,
                     const float z,
                     const Vector2d<float> &textureRepeats,
                     const glm::mat4 &translated = glm::mat4{1.0f},
                     const glm::mat4 &scaled = glm::mat4{1.0f},
                     const glm::mat4 &rotated = glm::mat4{1.0f});

    GraphicalPolygon(filing::JsonIO input);

    std::string dump(filing::JsonIO output, std::string nameField) override;

private:
    std::vector<Vector2d<float>> _shape;
    Vector2d<float> _textureRepeats;
};
} // namespace ample::graphics
