#pragma once

#include "box2d/b2_pulley_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldPulleyJoint2d : public WorldJoint2d
{
public:
	ample::graphics::Vector2d<float> getAnchorA() const override;
	ample::graphics::Vector2d<float> getAnchorB() const override;
	ample::graphics::Vector2d<float> getReactionForce(float inv_dt) const override;
	float getReactionTorque(float inv_dt) const override;

	ample::graphics::Vector2d<float> getGroundAnchorA() const;

	ample::graphics::Vector2d<float> getGroundAnchorB() const;

	float getLengthA() const;

	float getLengthB() const;

	float getRatio() const;

	float getCurrentLengthA() const;

	float getCurrentLengthB() const;

private:
	friend WorldLayer2d;

	WorldPulleyJoint2d(b2PulleyJoint *joint,
					   WorldObject2d &bodyA, WorldObject2d &bodyB,
					   const std::vector<ample::graphics::Vector2d<float>> &shape);
	b2PulleyJoint *_joint = nullptr;
};
} // namespace ample::physics