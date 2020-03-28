#pragma once
#include "box2d/b2_friction_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldFrictionJoint2d : public WorldJoint2d
{
public:
    ample::graphics::Vector2d<float> getLocalAnchorA() const;

    ample::graphics::Vector2d<float> getLocalAnchorB() const;

    void setMaxForce(float force);

    float getMaxForce() const;

    void setMaxTorque(float torque);

    float getMaxTorque() const;

private:
    friend WorldLayer2d;

    WorldFrictionJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB);
};
} // namespace ample::physics
