#pragma once

#include "box2d/b2_gear_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldGearJoint2d : public WorldJoint2d
{
public:
    WorldJoint2d &getJointA();
    WorldJoint2d &getJointB();

    void setRatio(float ratio);
    float getRatio() const;

    WorldGearJoint2d(WorldObject2d &bodyA,
                     WorldObject2d &bodyB,
                     WorldJoint2d &jointA,
                     WorldJoint2d &jointB,
                     float ratio = 1,
                     bool collideConnected = false);
    WorldJoint2d &_jointA;
    WorldJoint2d &_jointB;
};
} // namespace ample::physics
