#pragma once
#include "box2d/b2_motor_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
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

private:
    friend WorldLayer2d;

    WorldMotorJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB);
};
} // namespace ample::physics
