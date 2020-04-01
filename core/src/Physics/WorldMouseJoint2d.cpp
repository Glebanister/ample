#include "WorldMouseJoint2d.h"

namespace ample::physics
{
WorldMouseJoint2d::WorldMouseJoint2d(WorldObject2d &bodyA,
                                     WorldObject2d &bodyB,
                                     bool collideConnected)
    : WorldJoint2d(bodyA, bodyB)
{
    b2MouseJointDef jointDef;
    jointDef.bodyA = getB2Body(bodyA);
    jointDef.bodyB = getB2Body(bodyB);
    jointDef.collideConnected = collideConnected;
    initB2Joint(bodyA.getWorldLayer(), &jointDef);
}

void WorldMouseJoint2d::onActive()
{
    if (_form)
    {
        const ample::graphics::Vector2d<float> &target = getTarget();
        _form->setTranslate({(getAnchorB().x + target.x) / 2,
                             (getAnchorB().y + target.y) / 2, _bodyA.getZ()});
        float angle = atan((getAnchorB().x - target.x) / (getAnchorB().y - target.y));
        _form->setRotate({0.0f, 0.0f, 1.0f}, 180 - angle * 180.0f / M_PI);
        float curLength = sqrt(pow(getAnchorB().x - target.x, 2) + pow(getAnchorB().y - target.y, 2));
        _form->setScale({1.0f, curLength / _initLength, 1.0f});
    }
}

void WorldMouseJoint2d::setForm(graphics::GraphicalObject2d &form, float standardLength)
{
    _form = &form;
    _initLength = standardLength; //TODO check standardLength > 0
    _bodyA.getWorldLayer().addObject(form);
}

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
