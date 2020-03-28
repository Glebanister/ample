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
	ample::graphics::Vector2d<float> getGroundAnchorA() const;

	ample::graphics::Vector2d<float> getGroundAnchorB() const;

	float getLengthA() const;

	float getLengthB() const;

	float getRatio() const;

	float getCurrentLengthA() const;

	float getCurrentLengthB() const;

private:
	friend WorldLayer2d;

	WorldPulleyJoint2d(b2Joint *joint,
					   WorldObject2d &bodyA, WorldObject2d &bodyB);
};
} // namespace ample::physics
