#include "WorldPulleyJoint2d.h"

namespace ample::physics
{
WorldPulleyJoint2d::WorldPulleyJoint2d(WorldObject2d &bodyA,
                                       WorldObject2d &bodyB,
                                       const ample::graphics::Vector2d<float> &groundAnchorA,
                                       const ample::graphics::Vector2d<float> &groundAnchorB,
                                       const ample::graphics::Vector2d<float> &anchorA,
                                       const ample::graphics::Vector2d<float> &anchorB,
                                       float lengthA,
                                       float lengthB,
                                       float ratio,
                                       bool collideConnected)
    : WorldJoint2d(bodyA, bodyB)
{
    b2PulleyJointDef jointDef;
    jointDef.Initialize(getB2Body(bodyA), getB2Body(bodyB),
                        {groundAnchorA.x, groundAnchorA.y},
                        {groundAnchorB.x, groundAnchorB.y},
                        {anchorA.x, anchorA.y},
                        {anchorB.x, anchorB.y}, ratio);
    if (lengthA > 0)
    {
        jointDef.lengthA = lengthA;
    }
    if (lengthB > 0)
    {
        jointDef.lengthB = lengthB;
    }
    jointDef.collideConnected = collideConnected;
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

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
