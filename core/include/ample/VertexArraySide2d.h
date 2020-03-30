#pragma once

#include "VertexArray.h"
#include "Vector2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
class VertexArraySide2d final : public VertexArray
{
public:
    VertexArraySide2d(const std::vector<Vector2d<float>> &graphicalShape,
                      const float z,
                      const float depth,
                      const std::string &texturePath,
                      const Vector2d<int> &textureSize,
                      const Vector2d<int> &texturePos,
                      const Vector2d<textureMode> &texMode,
                      const normalsMode &normMode,
                      const channelMode &mode);
};
} // namespace ample::graphics