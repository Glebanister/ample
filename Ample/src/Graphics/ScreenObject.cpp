#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "ScreenObject.h"

namespace ample::graphics
{
ScreenObject::ScreenObject(const std::vector<Vector2d<float>> &shape,
                           Vector3d<float> position,
                           const float depth)
    : GraphicalObject2d(shape, depth, position.z) {}
} // namespace ample::graphics
