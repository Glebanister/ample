#pragma once
#include "box2d/b2_motor_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldMotorJoint2d : public WorldJoint2d
{
public:
    void setLinearOffset(const ample::graphics::Vector2d<float> &linearOffset);
    ample::graphics::Vector2d<float> getLinearOffset() const;

    void setAngularOffset(float angularOffset);
    float getAngularOffset() const;

    void setMaxForce(float force);

    float getMaxForce() const;

    void setMaxTorque(float torque);

    float getMaxTorque() const;

    void setCorrectionFactor(float factor);

    float getCorrectionFactor() const;

    WorldMotorJoint2d(const std::string &name,
                      WorldObject2d &bodyA,
                      WorldObject2d &bodyB,
                      bool collideConnected = false);
};
} // namespace ample::physics
