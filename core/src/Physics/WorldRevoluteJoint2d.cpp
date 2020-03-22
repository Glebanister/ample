#include "WorldRevoluteJoint2d.h"

namespace ample::physics
{
WorldRevoluteJoint2d::WorldRevoluteJoint2d(b2Joint *joint,
                                           WorldObject2d &bodyA, WorldObject2d &bodyB,
                                           const std::vector<ample::graphics::Vector2d<float>> &shape)
    : WorldJoint2d(joint, bodyA, bodyB, shape) {}

void WorldRevoluteJoint2d::onActive()
{
    const auto &posAnchor = static_cast<b2RevoluteJoint *>(_joint)->GetAnchorA();
    const auto &pos = _bodyA.getWorldPoint({posAnchor.x, posAnchor.y});
    setTranslate({pos.x, pos.y, getZ()});
    setRotate({0.0f, 0.0f, 1.0f}, 0);
}

ample::graphics::Vector2d<float> WorldRevoluteJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2RevoluteJoint *>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldRevoluteJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2RevoluteJoint *>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

float WorldRevoluteJoint2d::getReferenceAngle() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->GetReferenceAngle();
}

float WorldRevoluteJoint2d::getJointAngle() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->GetJointAngle();
}

float WorldRevoluteJoint2d::getJointSpeed() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->GetJointSpeed();
}

bool WorldRevoluteJoint2d::isLimitEnabled() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->IsLimitEnabled();
}

void WorldRevoluteJoint2d::enableLimit(bool flag)
{
    static_cast<b2RevoluteJoint *>(_joint)->EnableLimit(flag);
}

float WorldRevoluteJoint2d::getLowerLimit() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->GetLowerLimit();
}

float WorldRevoluteJoint2d::getUpperLimit() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->GetUpperLimit();
}

void WorldRevoluteJoint2d::setLimits(float lower, float upper)
{
    static_cast<b2RevoluteJoint *>(_joint)->SetLimits(lower, upper);
}

bool WorldRevoluteJoint2d::isMotorEnabled() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->IsMotorEnabled();
}

void WorldRevoluteJoint2d::enableMotor(bool flag)
{
    static_cast<b2RevoluteJoint *>(_joint)->EnableMotor(flag);
}

void WorldRevoluteJoint2d::setMotorSpeed(float speed)
{
    static_cast<b2RevoluteJoint *>(_joint)->SetMotorSpeed(speed);
}

float WorldRevoluteJoint2d::getMotorSpeed() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->GetMotorSpeed();
}

void WorldRevoluteJoint2d::setMaxMotorTorque(float torque)
{
    static_cast<b2RevoluteJoint *>(_joint)->SetMaxMotorTorque(torque);
}
float WorldRevoluteJoint2d::getMaxMotorTorque() const
{
    return static_cast<b2RevoluteJoint *>(_joint)->GetMaxMotorTorque();
}

float WorldRevoluteJoint2d::getMotorTorque(float inv_dt) const
{
    return static_cast<b2RevoluteJoint *>(_joint)->GetMotorTorque(inv_dt);
}
} // namespace ample::physics
