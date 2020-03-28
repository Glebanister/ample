#pragma once
#include "box2d/b2_weld_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldWeldJoint2d : public WorldJoint2d
{
public:
    ample::graphics::Vector2d<float> getLocalAnchorA() const;

    ample::graphics::Vector2d<float> getLocalAnchorB() const;

    float getReferenceAngle() const;

    void setFrequency(float hz);

    float getFrequency() const;

    void setDampingRatio(float ratio);

    float getDampingRatio() const;

private:
    friend WorldLayer2d;

    WorldWeldJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB);
};
} // namespace ample::physics
