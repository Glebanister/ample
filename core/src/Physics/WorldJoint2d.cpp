#include "WorldJoint2d.h"

namespace ample::physics
{
WorldJoint2d::WorldJoint2d(WorldObject2d &bodyA, WorldObject2d &bodyB,
                           const std::vector<ample::graphics::Vector2d<float>> &shape)
    : GraphicalObject2d(shape, 1, 1), _bodyA(bodyA), _bodyB(bodyB) {}

WorldObject2d &WorldJoint2d::getBodyA()
{
    return _bodyA;
}

WorldObject2d &WorldJoint2d::getBodyB()
{
    return _bodyB;
}
} // namespace ample::physics