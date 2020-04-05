#include "WorldPrismaticJoint2d.h"

namespace ample::physics
{
WorldPrismaticJoint2d::WorldPrismaticJoint2d(WorldObject2d &bodyA,
                                             WorldObject2d &bodyB,
                                             const ample::graphics::Vector2d<float> &anchor,
                                             const ample::graphics::Vector2d<float> &worldAxis,
                                             float referenceAngle,
                                             bool collideConnected)
    : WorldJoint2d(bodyA, bodyB)
{
    b2PrismaticJointDef jointDef;
    jointDef.Initialize(getB2Body(bodyA), getB2Body(bodyB),
                        {anchor.x, anchor.y},
                        {worldAxis.x, worldAxis.y});
    jointDef.referenceAngle = referenceAngle;
    jointDef.collideConnected = collideConnected;
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2PrismaticJoint *>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2PrismaticJoint *>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getLocalAxisA() const
{
    const b2Vec2 &axis = static_cast<b2PrismaticJoint *>(_joint)->GetLocalAxisA();
    return {axis.x, axis.y};
}

float WorldPrismaticJoint2d::getReferenceAngle() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->GetReferenceAngle();
}

float WorldPrismaticJoint2d::getJointTranslation() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->GetJointTranslation();
}

float WorldPrismaticJoint2d::getJointSpeed() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->GetJointSpeed();
}

bool WorldPrismaticJoint2d::isLimitEnabled() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->IsLimitEnabled();
}

void WorldPrismaticJoint2d::enableLimit(bool flag)
{
    static_cast<b2PrismaticJoint *>(_joint)->EnableLimit(flag);
}

float WorldPrismaticJoint2d::getLowerLimit() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->GetLowerLimit();
}

float WorldPrismaticJoint2d::getUpperLimit() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->GetUpperLimit();
}

void WorldPrismaticJoint2d::setLimits(float lower, float upper)
{
    static_cast<b2PrismaticJoint *>(_joint)->SetLimits(lower, upper);
}

bool WorldPrismaticJoint2d::isMotorEnabled() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->IsMotorEnabled();
}

void WorldPrismaticJoint2d::enableMotor(bool flag)
{
    static_cast<b2PrismaticJoint *>(_joint)->EnableMotor(flag);
}

void WorldPrismaticJoint2d::setMotorSpeed(float speed)
{
    static_cast<b2PrismaticJoint *>(_joint)->SetMotorSpeed(speed);
}

float WorldPrismaticJoint2d::getMotorSpeed() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->GetMotorSpeed();
}

void WorldPrismaticJoint2d::setMaxMotorForce(float force)
{
    static_cast<b2PrismaticJoint *>(_joint)->SetMaxMotorForce(force);
}
float WorldPrismaticJoint2d::getMaxMotorForce() const
{
    return static_cast<b2PrismaticJoint *>(_joint)->GetMaxMotorForce();
}

float WorldPrismaticJoint2d::getMotorForce(float inv_dt) const
{
    return static_cast<b2PrismaticJoint *>(_joint)->GetMotorForce(inv_dt);
}
} // namespace ample::physics
