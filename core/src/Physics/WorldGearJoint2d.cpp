#include "WorldGearJoint2d.h"

namespace ample::physics
{
WorldGearJoint2d::WorldGearJoint2d(const std::string &name,
                                   WorldObject2d &bodyA,
                                   WorldObject2d &bodyB,
                                   WorldJoint2d &jointA,
                                   WorldJoint2d &jointB,
                                   float ratio,
                                   bool collideConnected)
    : WorldJoint2d(name, "WorldGearJoint2d", bodyA, bodyB),
      _jointA(jointA), _jointB(jointB)
{
    b2GearJointDef jointDef;
    jointDef.bodyA = getB2Body(bodyA);
    jointDef.bodyB = getB2Body(bodyB);
    jointDef.joint1 = getB2Joint(jointA);
    jointDef.joint2 = getB2Joint(jointB);
    jointDef.ratio = ratio;
    jointDef.collideConnected = collideConnected;
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

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
