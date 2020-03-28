#pragma once

#include "box2d/b2_rope_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldRopeJoint2d : public WorldJoint2d
{
public:
    ample::graphics::Vector2d<float> getLocalAnchorA() const;
    ample::graphics::Vector2d<float> getLocalAnchorB() const;

    void setMaxLength(float length);
    float getMaxLength() const;

    //b2LimitState getLimitState() const;
private:
    friend WorldLayer2d;

    WorldRopeJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB);
};
} // namespace ample::physics
