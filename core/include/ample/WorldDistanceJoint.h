#pragma once
#include "box2d/b2_distance_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldDistanceJoint2d : public ample::physics::WorldJoint2d
{
public:
    ample::graphics::Vector2d<float> getLocalAnchorA() const;
    ample::graphics::Vector2d<float> getLocalAnchorB() const;

    void setLength(float length);
    float getLength() const;

    void setFrequency(float hz);
    float getFrequency() const;

    void setDampingRatio(float ratio);
    float getDampingRatio() const;

    WorldDistanceJoint2d(WorldObject2d &bodyA,
                         WorldObject2d &bodyB,
                         const ample::graphics::Vector2d<float> &anchorOnBodyA,
                         const ample::graphics::Vector2d<float> &anchorOnBodyB,
                         float length = -1,
                         bool collideConnected = false);
};
} // namespace ample::physics
