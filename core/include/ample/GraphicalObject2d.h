#pragma once

#include "GraphicalPolygon.h"
#include "GraphicalEdge.h"

namespace ample::filing
{
class GraphicalObject2dIO;
}

namespace ample::graphics
{
class GraphicalObject2d : public GraphicalObject
{
public:
    GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                      const float thickness,
                      const float z,
                      const Vector2d<float> &faceTextureRepeats,
                      const Vector2d<float> &sideTextureRepeats,
                      const normalsMode sideNormalsMode,
                      const glm::mat4 &translated = glm::mat4{1.0f},
                      const glm::mat4 &scaled = glm::mat4{1.0f},
                      const glm::mat4 &rotated = glm::mat4{1.0f});

    GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                      const float thickness,
                      const float z,
                      const Vector2d<float> &faceTextureRepeats,
                      const Vector2d<float> &sideTextureRepeats,
                      const normalsMode sideNormalsMode,
                      const Vector2d<float> &translated = {0.0f, 0.0f},
                      const float &rotated = 0.0f);

protected:
    GraphicalPolygon _face;
    GraphicalEdge _side;
};
} // namespace ample::graphics
