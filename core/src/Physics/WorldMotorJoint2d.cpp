#include "WorldMotorJoint2d.h"

namespace ample::physics
{
WorldMotorJoint2d::WorldMotorJoint2d(WorldObject2d &bodyA,
                                     WorldObject2d &bodyB,
                                     bool collideConnected)
    : WorldJoint2d(bodyA, bodyB)
{
    b2MotorJointDef jointDef;
    jointDef.Initialize(getB2Body(bodyA), getB2Body(bodyB));
    jointDef.collideConnected = collideConnected;
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

void WorldMotorJoint2d::setLinearOffset(const ample::graphics::Vector2d<float> &linearOffset)
{
    static_cast<b2MotorJoint *>(_joint)->SetLinearOffset({linearOffset.x, linearOffset.y});
}

ample::graphics::Vector2d<float> WorldMotorJoint2d::getLinearOffset() const
{
    const b2Vec2 &linearOffset = static_cast<b2MotorJoint *>(_joint)->GetLinearOffset();
    return {linearOffset.x, linearOffset.y};
}

void WorldMotorJoint2d::setAngularOffset(float angularOffset)
{
    static_cast<b2MotorJoint *>(_joint)->SetAngularOffset(angularOffset);
}

float WorldMotorJoint2d::getAngularOffset() const
{
    return static_cast<b2MotorJoint *>(_joint)->GetAngularOffset();
}

void WorldMotorJoint2d::setMaxForce(float force)
{
    static_cast<b2MotorJoint *>(_joint)->SetMaxForce(force);
}

float WorldMotorJoint2d::getMaxForce() const
{
    return static_cast<b2MotorJoint *>(_joint)->GetMaxForce();
}

void WorldMotorJoint2d::setMaxTorque(float torque)
{
    static_cast<b2MotorJoint *>(_joint)->SetMaxTorque(torque);
}

float WorldMotorJoint2d::getMaxTorque() const
{
    return static_cast<b2MotorJoint *>(_joint)->GetMaxTorque();
}

void WorldMotorJoint2d::setCorrectionFactor(float factor)
{
    static_cast<b2MotorJoint *>(_joint)->SetCorrectionFactor(factor);
}

float WorldMotorJoint2d::getCorrectionFactor() const
{
    return static_cast<b2MotorJoint *>(_joint)->GetCorrectionFactor();
}
} // namespace ample::physics
