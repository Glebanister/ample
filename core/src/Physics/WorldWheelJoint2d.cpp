#include "WorldWheelJoint2d.h"

namespace ample::physics
{
WorldWheelJoint2d::WorldWheelJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB)
    : WorldJoint2d(joint, bodyA, bodyB) {}

ample::graphics::Vector2d<float> WorldWheelJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2WheelJoint *>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldWheelJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2WheelJoint *>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldWheelJoint2d::getLocalAxisA() const
{
    const b2Vec2 &axis = static_cast<b2WheelJoint *>(_joint)->GetLocalAxisA();
    return {axis.x, axis.y};
}

float WorldWheelJoint2d::getJointTranslation() const
{
    return static_cast<b2WheelJoint *>(_joint)->GetJointTranslation();
}

float WorldWheelJoint2d::getJointLinearSpeed() const
{
    return static_cast<b2WheelJoint *>(_joint)->GetJointLinearSpeed();
}

float WorldWheelJoint2d::getJointAngle() const
{
    return static_cast<b2WheelJoint *>(_joint)->GetJointAngle();
}

float WorldWheelJoint2d::getJointAngularSpeed() const
{
    return static_cast<b2WheelJoint *>(_joint)->GetJointAngularSpeed();
}

bool WorldWheelJoint2d::isMotorEnabled() const
{
    return static_cast<b2WheelJoint *>(_joint)->IsMotorEnabled();
}

void WorldWheelJoint2d::enableMotor(bool flag)
{
    static_cast<b2WheelJoint *>(_joint)->EnableMotor(flag);
}

void WorldWheelJoint2d::setMotorSpeed(float speed)
{
    static_cast<b2WheelJoint *>(_joint)->SetMotorSpeed(speed);
}

float WorldWheelJoint2d::getMotorSpeed() const
{
    return static_cast<b2WheelJoint *>(_joint)->GetMotorSpeed();
}

void WorldWheelJoint2d::setMaxMotorTorque(float torque)
{
    static_cast<b2WheelJoint *>(_joint)->SetMaxMotorTorque(torque);
}

float WorldWheelJoint2d::getMaxMotorTorque() const
{
    return static_cast<b2WheelJoint *>(_joint)->GetMaxMotorTorque();
}

float WorldWheelJoint2d::getMotorTorque(float inv_dt) const
{
    return static_cast<b2WheelJoint *>(_joint)->GetMotorTorque(inv_dt);
}

void WorldWheelJoint2d::setSpringFrequencyHz(float hz)
{
    static_cast<b2WheelJoint *>(_joint)->SetSpringFrequencyHz(hz);
}

float WorldWheelJoint2d::getSpringFrequencyHz() const
{
    return static_cast<b2WheelJoint *>(_joint)->GetSpringFrequencyHz();
}

void WorldWheelJoint2d::setSpringDampingRatio(float ratio)
{
    static_cast<b2WheelJoint *>(_joint)->SetSpringDampingRatio(ratio);
}

float WorldWheelJoint2d::getSpringDampingRatio() const
{
    return static_cast<b2WheelJoint *>(_joint)->GetSpringDampingRatio();
}
} // namespace ample::physics
