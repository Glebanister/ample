#include "WorldDistanceJoint.h"
#include <cmath>
#include <iostream>
namespace ample::physics
{
WorldDistanceJoint2d::WorldDistanceJoint2d(b2Joint *joint,
                                           WorldObject2d &bodyA, WorldObject2d &bodyB,
                                           const std::vector<ample::graphics::Vector2d<float>> &shape)
    : WorldJoint2d(joint, bodyA, bodyB, shape) {}

void WorldDistanceJoint2d::onActive()
{
    setTranslate({(_bodyA.getPosition().x + _bodyB.getPosition().x) / 2,
                  (_bodyA.getPosition().y + _bodyB.getPosition().y) / 2, getZ()});
    float angle = atan(abs((_bodyA.getPosition().x - _bodyB.getPosition().x) / (_bodyA.getPosition().y - _bodyB.getPosition().y)));
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

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2DistanceJoint*>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2DistanceJoint*>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

void WorldDistanceJoint2d::setLength(float length)
{
    static_cast<b2DistanceJoint*>(_joint)->SetLength(length);
}

float WorldDistanceJoint2d::getLength() const
{
    return static_cast<b2DistanceJoint*>(_joint)->GetLength();
}

void WorldDistanceJoint2d::setFrequency(float hz)
{
    static_cast<b2DistanceJoint*>(_joint)->SetFrequency(hz);
}

float WorldDistanceJoint2d::getFrequency() const
{
    return static_cast<b2DistanceJoint*>(_joint)->GetFrequency();
}

void WorldDistanceJoint2d::setDampingRatio(float ratio)
{
    static_cast<b2DistanceJoint*>(_joint)->SetDampingRatio(ratio);
}

float WorldDistanceJoint2d::getDampingRatio() const
{
    return static_cast<b2DistanceJoint*>(_joint)->GetDampingRatio();
}
} // namespace ample::physics