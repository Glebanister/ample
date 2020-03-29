#pragma once

#include "box2d/b2_mouse_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldMouseJoint2d : public WorldJoint2d
{
public:
    void setTarget(const ample::graphics::Vector2d<float> &target);
    ample::graphics::Vector2d<float> getTarget() const;

    void setMaxForce(float force);
    float getMaxForce() const;

    void setFrequency(float hz);
    float getFrequency() const;

    void setDampingRatio(float ratio);
    float getDampingRatio() const;

    WorldMouseJoint2d(WorldObject2d &bodyA,
                      WorldObject2d &bodyB,
                      bool collideConnected = false);
};
} // namespace ample::physics
