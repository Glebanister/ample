#include "WorldRopeJoint2d.h"

namespace ample::physics
{
WorldRopeJoint2d::WorldRopeJoint2d(WorldObject2d &bodyA,
                                   WorldObject2d &bodyB,
                                   const ample::graphics::Vector2d<float> &localAnchorA,
                                   const ample::graphics::Vector2d<float> &localAnchorB,
                                   float maxLength,
                                   bool collideConnected)
    : WorldJoint2d(bodyA, bodyB)
{
    b2RopeJointDef jointDef;
    jointDef.bodyA = getB2Body(bodyA);
    jointDef.bodyB = getB2Body(bodyB);
    jointDef.localAnchorA.Set(localAnchorA.x, localAnchorA.y);
    jointDef.localAnchorB.Set(localAnchorB.x, localAnchorB.y);
    jointDef.maxLength = maxLength;
    jointDef.collideConnected = collideConnected;
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

ample::graphics::Vector2d<float> WorldRopeJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2RopeJoint *>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldRopeJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2RopeJoint *>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

void WorldRopeJoint2d::setMaxLength(float length)
{
    static_cast<b2RopeJoint *>(_joint)->SetMaxLength(length);
}

float WorldRopeJoint2d::getMaxLength() const
{
    return static_cast<b2RopeJoint *>(_joint)->GetMaxLength();
}
} // namespace ample::physics
