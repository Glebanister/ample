#include "WorldDistanceJoint.h"
#include <cmath>
#include <iostream>
namespace ample::physics
{
WorldDistanceJoint2d::WorldDistanceJoint2d(WorldObject2d &bodyA,
                                           WorldObject2d &bodyB,
                                           const ample::graphics::Vector2d<float> &anchorOnBodyA,
                                           const ample::graphics::Vector2d<float> &anchorOnBodyB,
                                           float length,
                                           bool collideConnected)
    : WorldJoint2d(bodyA, bodyB)
{
    b2DistanceJointDef jointDef;
    jointDef.Initialize(getB2Body(bodyA), getB2Body(bodyB),
                        {anchorOnBodyA.x, anchorOnBodyA.y},
                        {anchorOnBodyB.x, anchorOnBodyB.y});
    jointDef.collideConnected = collideConnected;
    if (length > 0)
    {
        jointDef.length = length;
    }
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

void WorldDistanceJoint2d::onActive()
{
    if (_form)
    {
        _form->setTranslate({(getAnchorA().x + getAnchorB().x) / 2,
                             (getAnchorA().y + getAnchorB().y) / 2, _bodyA.getZ()});
        float angle = atan((getAnchorA().x - getAnchorB().x) / (getAnchorA().y - getAnchorB().y));
        _form->setRotate({0.0f, 0.0f, 1.0f}, 180 - angle * 180.0f / M_PI);
        float curLength = sqrt(pow(getAnchorA().x - getAnchorB().x, 2) + pow(getAnchorA().y - getAnchorB().y, 2));
        _form->setScale({1.0f, curLength / _initLength, 1.0f});
    }
}

void WorldDistanceJoint2d::setForm(graphics::GraphicalObject2d &form)
{
    _form = &form;
    _initLength = getLength();
    _bodyA.getWorldLayer().addObject(form);
}

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getLocalAnchorA() const
{
    const b2Vec2 &anchor = static_cast<b2DistanceJoint *>(_joint)->GetLocalAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldDistanceJoint2d::getLocalAnchorB() const
{
    const b2Vec2 &anchor = static_cast<b2DistanceJoint *>(_joint)->GetLocalAnchorB();
    return {anchor.x, anchor.y};
}

void WorldDistanceJoint2d::setLength(float length)
{
    static_cast<b2DistanceJoint *>(_joint)->SetLength(length);
}

float WorldDistanceJoint2d::getLength() const
{
    return static_cast<b2DistanceJoint *>(_joint)->GetLength();
}

void WorldDistanceJoint2d::setFrequency(float hz)
{
    static_cast<b2DistanceJoint *>(_joint)->SetFrequency(hz);
}

float WorldDistanceJoint2d::getFrequency() const
{
    return static_cast<b2DistanceJoint *>(_joint)->GetFrequency();
}

void WorldDistanceJoint2d::setDampingRatio(float ratio)
{
    static_cast<b2DistanceJoint *>(_joint)->SetDampingRatio(ratio);
}

float WorldDistanceJoint2d::getDampingRatio() const
{
    return static_cast<b2DistanceJoint *>(_joint)->GetDampingRatio();
}
} // namespace ample::physics