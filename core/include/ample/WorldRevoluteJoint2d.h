#pragma once
#include "box2d/b2_revolute_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldRevoluteJoint2d : public WorldJoint2d
{
public:
	void onActive() override;

	ample::graphics::Vector2d<float> getAnchorA() const override;
	ample::graphics::Vector2d<float> getAnchorB() const override;
	ample::graphics::Vector2d<float> getReactionForce(float inv_dt) const override;
	float getReactionTorque(float inv_dt) const override;

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

private:
	friend ample::physics::WorldLayer2d;

	WorldRevoluteJoint2d(b2RevoluteJoint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB,
						 const std::vector<ample::graphics::Vector2d<float>> &shape);
	b2RevoluteJoint *_joint = nullptr;
};
} // namespace ample::physics
