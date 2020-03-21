#include "WorldRevoluteJoint2d.h"

namespace ample::physics
{
WorldRevoluteJoint2d::WorldRevoluteJoint2d(b2RevoluteJoint *joint,
                                           WorldObject2d &bodyA, WorldObject2d &bodyB,
                                           const std::vector<ample::graphics::Vector2d<float>> &shape)
    : WorldJoint2d(bodyA, bodyB, shape), _joint(joint) {}

void WorldRevoluteJoint2d::onActive()
{
    const auto &posAnchor = _joint->GetAnchorA();
    const auto &pos = _bodyA.getWorldPoint({posAnchor.x, posAnchor.y});
    setTranslate({pos.x, pos.y, getZ()});
    setRotate({0.0f, 0.0f, 1.0f}, 0);
}

ample::graphics::Vector2d<float> WorldRevoluteJoint2d::getAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldRevoluteJoint2d::getAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldRevoluteJoint2d::getReactionForce(float inv_dt) const
{
    const b2Vec2 &force = _joint->GetReactionForce(inv_dt);
    return {force.x, force.y};
}

float WorldRevoluteJoint2d::getReactionTorque(float inv_dt) const
{
    return _joint->GetReactionTorque(inv_dt);
}

ample::graphics::Vector2d<float> WorldRevoluteJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldRevoluteJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

float WorldRevoluteJoint2d::getReferenceAngle() const
{
    return _joint->GetReferenceAngle();
}

float WorldRevoluteJoint2d::getJointAngle() const
{
    return _joint->GetJointAngle();
}

float WorldRevoluteJoint2d::getJointSpeed() const
{
    return _joint->GetJointSpeed();
}

bool WorldRevoluteJoint2d::isLimitEnabled() const
{
    return _joint->IsLimitEnabled();
}

void WorldRevoluteJoint2d::enableLimit(bool flag)
{
    _joint->EnableLimit(flag);
}

float WorldRevoluteJoint2d::getLowerLimit() const
{
    return _joint->GetLowerLimit();
}

float WorldRevoluteJoint2d::getUpperLimit() const
{
    return _joint->GetUpperLimit();
}

void WorldRevoluteJoint2d::setLimits(float lower, float upper)
{
    _joint->SetLimits(lower, upper);
}

bool WorldRevoluteJoint2d::isMotorEnabled() const
{
    return _joint->IsMotorEnabled();
}

void WorldRevoluteJoint2d::enableMotor(bool flag)
{
    _joint->EnableMotor(flag);
}

void WorldRevoluteJoint2d::setMotorSpeed(float speed)
{
    _joint->SetMotorSpeed(speed);
}

float WorldRevoluteJoint2d::getMotorSpeed() const
{
    return _joint->GetMotorSpeed();
}

void WorldRevoluteJoint2d::setMaxMotorTorque(float torque)
{
    _joint->SetMaxMotorTorque(torque);
}
float WorldRevoluteJoint2d::getMaxMotorTorque() const
{
    return _joint->GetMaxMotorTorque();
}

float WorldRevoluteJoint2d::getMotorTorque(float inv_dt) const
{
    return _joint->GetMotorTorque(inv_dt);
}
} // namespace ample::physics