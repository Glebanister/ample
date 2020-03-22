#pragma once

#include "box2d/b2_prismatic_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldPrismaticJoint2d : public WorldJoint2d
{
public:
	ample::graphics::Vector2d<float> getAnchorA() const override;
	ample::graphics::Vector2d<float> getAnchorB() const override;
	ample::graphics::Vector2d<float> getReactionForce(float inv_dt) const override;
	float getReactionTorque(float inv_dt) const override;

	ample::graphics::Vector2d<float> getLocalAnchorA() const;
	ample::graphics::Vector2d<float> getLocalAnchorB() const;

	ample::graphics::Vector2d<float> getLocalAxisA() const;

	float getReferenceAngle() const;

	float getJointTranslation() const;

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

	void setMaxMotorForce(float force);
	float getMaxMotorForce() const;

	float getMotorForce(float inv_dt) const;

private:
	friend WorldLayer2d;

	WorldPrismaticJoint2d(b2PrismaticJoint *joint,
						  WorldObject2d &bodyA, WorldObject2d &bodyB,
						  const std::vector<ample::graphics::Vector2d<float>> &shape);
	b2PrismaticJoint *_joint = nullptr;
};
} // namespace ample::physics