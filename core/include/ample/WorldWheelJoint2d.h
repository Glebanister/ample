#pragma once

#include "box2d/b2_wheel_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldWheelJoint2d : public WorldJoint2d
{
public:
	ample::graphics::Vector2d<float> getLocalAnchorA() const;

	ample::graphics::Vector2d<float> getLocalAnchorB() const;

	ample::graphics::Vector2d<float> getLocalAxisA() const;

	float getJointTranslation() const;

	float getJointLinearSpeed() const;

	float getJointAngle() const;

	float getJointAngularSpeed() const;

	bool isMotorEnabled() const;

	void enableMotor(bool flag);

	void setMotorSpeed(float speed);

	float getMotorSpeed() const;

	void setMaxMotorTorque(float torque);
	float getMaxMotorTorque() const;

	float getMotorTorque(float inv_dt) const;

	void setSpringFrequencyHz(float hz);
	float getSpringFrequencyHz() const;

	void setSpringDampingRatio(float ratio);
	float getSpringDampingRatio() const;

	WorldWheelJoint2d(WorldObject2d &bodyA,
					  WorldObject2d &bodyB,
					  const ample::graphics::Vector2d<float> &anchor,
					  const ample::graphics::Vector2d<float> &axis = {1.0, 0.0},
					  bool collideConnected = false);
};
} // namespace ample::physics
