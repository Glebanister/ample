#pragma once

#include "box2d/b2_pulley_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
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

	WorldPulleyJoint2d(WorldObject2d &bodyA,
					   WorldObject2d &bodyB,
					   const ample::graphics::Vector2d<float> &groundAnchorA,
					   const ample::graphics::Vector2d<float> &groundAnchorB,
					   const ample::graphics::Vector2d<float> &anchorA,
					   const ample::graphics::Vector2d<float> &anchorB,
					   float lengthA = -1,
					   float lengthB = -1,
					   float ratio = 1,
					   bool collideConnected = false);
};
} // namespace ample::physics
