#pragma once

#include "box2d/b2_joint.h"
#include "WorldObject2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldJoint2d
{
public:
    WorldObject2d &getBodyA();
    WorldObject2d &getBodyB();
    virtual ample::graphics::Vector2d<float> getAnchorA() const;
    virtual ample::graphics::Vector2d<float> getAnchorB() const;
    virtual ample::graphics::Vector2d<float> getReactionForce(float inv_dt) const;
    virtual float getReactionTorque(float inv_dt) const;

protected:
    friend WorldLayer2d;

    WorldJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB);
    b2Joint *_joint = nullptr;
    WorldObject2d &_bodyA;
    WorldObject2d &_bodyB;
};
} // namespace ample::physics