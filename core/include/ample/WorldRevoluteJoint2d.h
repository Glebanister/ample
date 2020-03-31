#pragma once
#include "box2d/b2_revolute_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldRevoluteJoint2d : public WorldJoint2d
{
public:
	ample::graphics::Vector2d<float> getLocalAnchorA() const;
	ample::graphics::Vector2d<float> getLocalAnchorB() const;

	float getReferenceAngle() const;

	float getJointAngle() const;

	float getJointSpeed() const;

	bool isLimitEnabled() const;

	void enableLimit(bool flag);

	float getLowerLimit() const;

	float getUpperLimit() const;

	void setLimits(float lower, float upper);

	bool isMotorEnabled() const;

	void enableMotor(bool flag);

	void setMotorSpeed(float speed);

	float getMotorSpeed() const;

	void setMaxMotorTorque(float torque);
	float getMaxMotorTorque() const;

	float getMotorTorque(float inv_dt) const;

	WorldRevoluteJoint2d(WorldObject2d &bodyA,
						 WorldObject2d &bodyB,
						 const ample::graphics::Vector2d<float> &anchor,
						 float referenceAngle = 0,
						 bool collideConnected = false);
};
} // namespace ample::physics
