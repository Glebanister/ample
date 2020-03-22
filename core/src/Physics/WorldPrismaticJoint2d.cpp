#include "WorldPrismaticJoint2d.h"

namespace ample::physics
{
WorldPrismaticJoint2d::WorldPrismaticJoint2d(b2PrismaticJoint *joint,
                                             WorldObject2d &bodyA, WorldObject2d &bodyB,
                                             const std::vector<ample::graphics::Vector2d<float>> &shape)
    : WorldJoint2d(bodyA, bodyB, shape), _joint(joint) {}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getReactionForce(float inv_dt) const
{
    const b2Vec2 &force = _joint->GetReactionForce(inv_dt);
    return {force.x, force.y};
}

float WorldPrismaticJoint2d::getReactionTorque(float inv_dt) const
{
    return _joint->GetReactionTorque(inv_dt);
}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPrismaticJoint2d::getLocalAxisA() const
{
    const b2Vec2 &axis = _joint->GetLocalAxisA();
    return {axis.x, axis.y};
}

float WorldPrismaticJoint2d::getReferenceAngle() const
{
    return _joint->GetReferenceAngle();
}

float WorldPrismaticJoint2d::getJointTranslation() const
{
    return _joint->GetJointTranslation();
}

float WorldPrismaticJoint2d::getJointSpeed() const
{
    return _joint->GetJointSpeed();
}

bool WorldPrismaticJoint2d::isLimitEnabled() const
{
    return _joint->IsLimitEnabled();
}

void WorldPrismaticJoint2d::enableLimit(bool flag)
{
    _joint->EnableLimit(flag);
}

float WorldPrismaticJoint2d::getLowerLimit() const
{
    return _joint->GetLowerLimit();
}

float WorldPrismaticJoint2d::getUpperLimit() const
{
    return _joint->GetUpperLimit();
}

void WorldPrismaticJoint2d::setLimits(float lower, float upper)
{
    _joint->SetLimits(lower, upper);
}

bool WorldPrismaticJoint2d::isMotorEnabled() const
{
    return _joint->IsMotorEnabled();
}

void WorldPrismaticJoint2d::enableMotor(bool flag)
{
    _joint->EnableMotor(flag);
}

void WorldPrismaticJoint2d::setMotorSpeed(float speed)
{
    _joint->SetMotorSpeed(speed);
}

float WorldPrismaticJoint2d::getMotorSpeed() const
{
    return _joint->GetMotorSpeed();
}

void WorldPrismaticJoint2d::setMaxMotorForce(float force)
{
    _joint->SetMaxMotorForce(force);
}
float WorldPrismaticJoint2d::getMaxMotorForce() const
{
    return _joint->GetMaxMotorForce();
}

float WorldPrismaticJoint2d::getMotorForce(float inv_dt) const
{
    return _joint->GetMotorForce(inv_dt);
}
} // namespace ample::physics
