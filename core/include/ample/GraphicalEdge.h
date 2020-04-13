#pragma once

#include <string>
#include <vector>

#include "GraphicalObject.h"

enum class normalsMode
{
    FACE,
    VERTEX,
};

namespace ample::graphics
{
class GraphicalEdge final : public GraphicalObject
{
public:
    GraphicalEdge(const std::string &name,
                  const std::vector<Vector2d<float>> &shape,
                  const float z,
                  const float thickness,
                  const Vector2d<float> &textureRepeats,
                  const normalsMode normMode,
                  const glm::mat4 &translated = glm::mat4{1.0f},
                  const glm::mat4 &scaled = glm::mat4{1.0f},
                  const glm::mat4 &rotated = glm::mat4{1.0f});

    explicit GraphicalEdge(filing::JsonIO input);

    std::string dump() override;

private:
    std::vector<Vector2d<float>> _shape;
    const float _thickness;
    const Vector2d<float> _textureRepeats;
    const normalsMode _normMode;
};
} // namespace ample::graphics
