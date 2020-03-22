#include "WorldPulleyJoint2d.h"

namespace ample::physics
{
WorldPulleyJoint2d::WorldPulleyJoint2d(b2Joint *joint,
                                       WorldObject2d &bodyA, WorldObject2d &bodyB,
                                       const std::vector<ample::graphics::Vector2d<float>> &shape)
    : WorldJoint2d(joint, bodyA, bodyB, shape) {}

ample::graphics::Vector2d<float> WorldPulleyJoint2d::getGroundAnchorA() const
{
    b2Vec2 anchor = static_cast<b2PulleyJoint *>(_joint)->GetGroundAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldPulleyJoint2d::getGroundAnchorB() const
{
    b2Vec2 anchor = static_cast<b2PulleyJoint *>(_joint)->GetGroundAnchorB();
    return {anchor.x, anchor.y};
}

float WorldPulleyJoint2d::getLengthA() const
{
    return static_cast<b2PulleyJoint *>(_joint)->GetLengthA();
}

float WorldPulleyJoint2d::getLengthB() const
{
    return static_cast<b2PulleyJoint *>(_joint)->GetLengthB();
}

float WorldPulleyJoint2d::getRatio() const
{
    return static_cast<b2PulleyJoint *>(_joint)->GetRatio();
}

float WorldPulleyJoint2d::getCurrentLengthA() const
{
    return static_cast<b2PulleyJoint *>(_joint)->GetCurrentLengthA();
}

float WorldPulleyJoint2d::getCurrentLengthB() const
{
    return static_cast<b2PulleyJoint *>(_joint)->GetCurrentLengthB();
}
} // namespace ample::physics
