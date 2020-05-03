#pragma once
#include "box2d/b2_weld_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
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

    WorldWeldJoint2d(const std::string &name,
                     WorldObject2d &bodyA,
                     WorldObject2d &bodyB,
                     const ample::graphics::Vector2d<float> &anchor,
                     float referenceAngle = 0,
                     bool collideConnected = false);
};
} // namespace ample::physics
