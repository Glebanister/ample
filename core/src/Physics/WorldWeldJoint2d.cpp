#include "WorldWeldJoint2d.h"

namespace ample::physics
{
WorldWeldJoint2d::WorldWeldJoint2d(const std::string &name,
                                   WorldObject2d &bodyA,
                                   WorldObject2d &bodyB,
                                   const ample::graphics::Vector2d<float> &anchor,
                                   float referenceAngle,
                                   bool collideConnected)
    : WorldJoint2d(name, "WorldWeldJoint2d", bodyA, bodyB)
{
    b2WeldJointDef jointDef;
    jointDef.Initialize(getB2Body(bodyA), getB2Body(bodyB), {anchor.x, anchor.y});
    jointDef.referenceAngle = referenceAngle;
    jointDef.collideConnected = collideConnected;
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

ample::graphics::Vector2d<float> WorldWeldJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2WeldJoint *>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldWeldJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2WeldJoint *>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

float WorldWeldJoint2d::getReferenceAngle() const
{
    return static_cast<b2WeldJoint *>(_joint)->GetReferenceAngle();
}

void WorldWeldJoint2d::setFrequency(float hz)
{
    static_cast<b2WeldJoint *>(_joint)->SetFrequency(hz);
}

float WorldWeldJoint2d::getFrequency() const
{
    return static_cast<b2WeldJoint *>(_joint)->GetFrequency();
}

void WorldWeldJoint2d::setDampingRatio(float ratio)
{
    static_cast<b2WeldJoint *>(_joint)->SetDampingRatio(ratio);
}

float WorldWeldJoint2d::getDampingRatio() const
{
    return static_cast<b2WeldJoint *>(_joint)->GetDampingRatio();
}
} // namespace ample::physics
