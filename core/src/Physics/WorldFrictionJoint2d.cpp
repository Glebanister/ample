#include "WorldFrictionJoint2d.h"

namespace ample::physics
{
WorldFrictionJoint2d::WorldFrictionJoint2d(const std::string &name,
                                           WorldObject2d &bodyA,
                                           WorldObject2d &bodyB,
                                           const ample::graphics::Vector2d<float> &anchor,
                                           bool collideConnected)
    : WorldJoint2d(name, "WorldFrictionJoint2d", bodyA, bodyB)
{
    b2FrictionJointDef jointDef;
    jointDef.Initialize(getB2Body(bodyA), getB2Body(bodyB), {anchor.x, anchor.y});
    jointDef.collideConnected = collideConnected;
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

ample::graphics::Vector2d<float> WorldFrictionJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2FrictionJoint *>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldFrictionJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2FrictionJoint *>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

void WorldFrictionJoint2d::setMaxForce(float force)
{
    static_cast<b2FrictionJoint *>(_joint)->SetMaxForce(force);
}

float WorldFrictionJoint2d::getMaxForce() const
{
    return static_cast<b2FrictionJoint *>(_joint)->GetMaxForce();
}

void WorldFrictionJoint2d::setMaxTorque(float torque)
{
    static_cast<b2FrictionJoint *>(_joint)->SetMaxTorque(torque);
}

float WorldFrictionJoint2d::getMaxTorque() const
{
    return static_cast<b2FrictionJoint *>(_joint)->GetMaxTorque();
}
} // namespace ample::physics
