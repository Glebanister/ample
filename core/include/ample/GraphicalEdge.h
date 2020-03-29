#pragma once

#include <string>
#include <vector>

#include "GraphicalObject.h"

namespace ample::graphics
{
enum class normalsMode
{
    SINGLE,
    VERTEX,
};

class GraphicalEdge : public GraphicalObject
{
public:
    GraphicalEdge(const std::vector<Vector2d<float>> &shape,
                  const float z,
                  const float thickness,
                  const Vector2d<float> &textureRepeats,
                  const normalsMode normMode,
                  const glm::mat4 &translated = glm::mat4{1.0f},
                  const glm::mat4 &scaled = glm::mat4{1.0f},
                  const glm::mat4 &rotated = glm::mat4{1.0f});

private:
    std::vector<Vector2d<float>> _shape;
    VertexArray _vertexArray;
};
} // namespace ample::graphics
