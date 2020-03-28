#include "WorldGearJoint2d.h"

namespace ample::physics
{
WorldGearJoint2d::WorldGearJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB,
                                   WorldJoint2d &jointA, WorldJoint2d &jointB)
    : WorldJoint2d(joint, bodyA, bodyB), _jointA(jointA), _jointB(jointB) {}

WorldJoint2d &WorldGearJoint2d::getJointA()
{
    return _jointA;
}
WorldJoint2d &WorldGearJoint2d::getJointB()
{
    return _jointB;
}

void WorldGearJoint2d::setRatio(float ratio)
{
    static_cast<b2GearJoint *>(_joint)->SetRatio(ratio);
}
float WorldGearJoint2d::getRatio() const
{
    return static_cast<b2GearJoint *>(_joint)->GetRatio();
}
} // namespace ample::physics
