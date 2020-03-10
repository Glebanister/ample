#pragma once

#define GL_GLEXT_PROTOTYPES 1
#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <glm/gtx/transform.hpp>

#include "GraphicalObject2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
using pixel_t = std::int32_t;
using radian_t = float;

class ScreenObject : public GraphicalObject2d
{
public:
    ScreenObject(const std::vector<Vector2d<float>> &shape,
                 Vector3d<float> position,
                 const float depth);
};
} // namespace ample::graphics
