#pragma once

#include "box2d/b2_gear_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldGearJoint2d : public WorldJoint2d
{
public:
    WorldJoint2d &getJointA();
    WorldJoint2d &getJointB();

    void setRatio(float ratio);
    float getRatio() const;

private:
    friend WorldLayer2d;

    WorldGearJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB,
                     WorldJoint2d &joinA, WorldJoint2d &jointB);
    WorldJoint2d &_jointA;
    WorldJoint2d &_jointB;
};
} // namespace ample::physics
