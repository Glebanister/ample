#include "WorldMouseJoint2d.h"

namespace ample::physics
{
WorldMouseJoint2d::WorldMouseJoint2d(b2Joint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB)
    : WorldJoint2d(joint, bodyA, bodyB) {}

void WorldMouseJoint2d::setTarget(const ample::graphics::Vector2d<float> &target)
{
    static_cast<b2MouseJoint *>(_joint)->SetTarget({target.x, target.y});
}

ample::graphics::Vector2d<float> WorldMouseJoint2d::getTarget() const
{
    const auto &target = static_cast<b2MouseJoint *>(_joint)->GetTarget();
    return {target.x, target.y};
}

void WorldMouseJoint2d::setMaxForce(float force)
{
    static_cast<b2MouseJoint *>(_joint)->SetMaxForce(force);
}

float WorldMouseJoint2d::getMaxForce() const
{
    return static_cast<b2MouseJoint *>(_joint)->GetMaxForce();
}

void WorldMouseJoint2d::setFrequency(float hz)
{
    static_cast<b2MouseJoint *>(_joint)->SetFrequency(hz);
}

float WorldMouseJoint2d::getFrequency() const
{
    return static_cast<b2MouseJoint *>(_joint)->GetFrequency();
}

void WorldMouseJoint2d::setDampingRatio(float ratio)
{
    static_cast<b2MouseJoint *>(_joint)->SetDampingRatio(ratio);
}

float WorldMouseJoint2d::getDampingRatio() const
{
    return static_cast<b2MouseJoint *>(_joint)->GetDampingRatio();
}
} // namespace ample::physics