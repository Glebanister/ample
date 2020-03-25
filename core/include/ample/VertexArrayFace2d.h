#pragma once

#include <vector>

#include "VertexArray.h"

namespace ample::graphics
{
class VertexArrayFace2d final : public VertexArray
{
public:
    VertexArrayFace2d(const std::vector<Vector2d<float>> &graphicalShape,
                      const float z,
                      const std::string &texturePath,
                      const Vector2d<float> &textureSize,
                      const Vector2d<float> &texturePos,
                      const Vector2d<textureMode> &texMode);

private:

};
} // namespace ample::graphics
