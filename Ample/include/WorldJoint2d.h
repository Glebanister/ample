#pragma once
#include "WorldObject2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldJoint2d : public ample::graphics::GraphicalObject2d
{
public:
    WorldObject2d &getBodyA();
    WorldObject2d &getBodyB();
    virtual ample::graphics::Vector2d<float> getAnchorA() const = 0;
    virtual ample::graphics::Vector2d<float> getAnchorB() const = 0;
    virtual ample::graphics::Vector2d<float> getReactionForce(float inv_dt) const = 0;
    virtual float getReactionTorque(float inv_dt) const = 0;

protected:
    WorldJoint2d(WorldObject2d &bodyA, WorldObject2d &bodyB, const std::vector<ample::graphics::Vector2d<float>>& shape);
    WorldObject2d &_bodyA;
    WorldObject2d &_bodyB;
};
} // namespace ample::physics