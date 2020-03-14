#include "WorldDistanceJoint.h"
#include <cmath>
#include <iostream>
namespace ample::physics
{
WorldDistanceJoint2d::WorldDistanceJoint2d(b2DistanceJoint *joint,
                                           WorldObject2d &bodyA, WorldObject2d &bodyB,
                                           const std::vector<ample::graphics::Vector2d<float>> &shape)
    : WorldJoint2d(bodyA, bodyB, shape), _joint(joint) {}

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetAnchorA();
    return {anchor.x, anchor.y};
}

void WorldDistanceJoint2d::onActive()
{
    setTranslate({(_bodyA.getPosition().x + _bodyB.getPosition().x) / 2,
                  (_bodyA.getPosition().y + _bodyB.getPosition().y) / 2, getZ()});

    float gip = getLength();
    float angle = acos(std::min((float)1, abs(_bodyA.getPosition().y - _bodyB.getPosition().y) / gip));
    if (_bodyA.getPosition().y >= _bodyB.getPosition().y)
    {
        if (_bodyA.getPosition().x > _bodyB.getPosition().x)
        {
            setRotate({0.0f, 0.0f, 1.0f}, 180 - angle * 180.0f / M_PI);
        }
        else
        {
            setRotate({0.0f, 0.0f, 1.0f}, angle * 180.0f / M_PI);
        }
    }
    else
    {
        if (_bodyA.getPosition().x > _bodyB.getPosition().x)
        {
            setRotate({0.0f, 0.0f, 1.0f}, angle * 180.0f / M_PI);
        }
        else
        {
            setRotate({0.0f, 0.0f, 1.0f}, 180 - angle * 180.0f / M_PI);
        }
    }
}

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getReactionForce(float inv_dt) const
{
    const b2Vec2 &force = _joint->GetReactionForce(inv_dt);
    return {force.x, force.y};
}

float WorldDistanceJoint2d::getReactionTorque(float inv_dt) const
{
    return _joint->GetReactionTorque(inv_dt);
}

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

void WorldDistanceJoint2d::setLength(float length)
{
    _joint->SetLength(length);
}

float WorldDistanceJoint2d::getLength() const
{
    return _joint->GetLength();
}

void WorldDistanceJoint2d::setFrequency(float hz)
{
    _joint->SetFrequency(hz);
}

float WorldDistanceJoint2d::getFrequency() const
{
    return _joint->GetFrequency();
}
} // namespace ample::physics