#include "WorldPulleyJoint2d.h"

namespace ample::physics
{
WorldPulleyJoint2d::WorldPulleyJoint2d(b2PulleyJoint *joint,
                                       WorldObject2d &bodyA, WorldObject2d &bodyB,
                                       const std::vector<ample::graphics::Vector2d<float>> &shape)
    : WorldJoint2d(bodyA, bodyB, shape), _joint(joint) {}

ample::graphics::Vector2d<float> WorldPulleyJoint2d::getAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPulleyJoint2d::getAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPulleyJoint2d::getReactionForce(float inv_dt) const
{
    const b2Vec2 &force = _joint->GetReactionForce(inv_dt);
    return {force.x, force.y};
}

float WorldPulleyJoint2d::getReactionTorque(float inv_dt) const
{
    return _joint->GetReactionTorque(inv_dt);
}

ample::graphics::Vector2d<float> WorldPulleyJoint2d::getGroundAnchorA() const
{
    b2Vec2 anchor = _joint->GetGroundAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPulleyJoint2d::getGroundAnchorB() const
{
    b2Vec2 anchor = _joint->GetGroundAnchorB();
    return {anchor.x, anchor.y};
}

float WorldPulleyJoint2d::getLengthA() const
{
    return _joint->GetLengthA();
}

float WorldPulleyJoint2d::getLengthB() const
{
    return _joint->GetLengthB();
}

float WorldPulleyJoint2d::getRatio() const
{
    return _joint->GetRatio();
}

float WorldPulleyJoint2d::getCurrentLengthA() const
{
    return _joint->GetCurrentLengthA();
}

float WorldPulleyJoint2d::getCurrentLengthB() const
{
    return _joint->GetCurrentLengthB();
}
} // namespace ample::physics
