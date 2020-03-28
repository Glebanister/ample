#include "WorldRopeJoint2d.h"

namespace ample::physics
{
WorldRopeJoint2d::WorldRopeJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB)
    : WorldJoint2d(joint, bodyA, bodyB) {}

ample::graphics::Vector2d<float> WorldRopeJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2RopeJoint *>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldRopeJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2RopeJoint *>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

void WorldRopeJoint2d::setMaxLength(float length)
{
    static_cast<b2RopeJoint *>(_joint)->SetMaxLength(length);
}

float WorldRopeJoint2d::getMaxLength() const
{
    return static_cast<b2RopeJoint *>(_joint)->GetMaxLength();
}
} // namespace ample::physics
