#include "WorldJoint2d.h"

namespace ample::physics
{
WorldJoint2d::WorldJoint2d(const std::string &name,
                           const std::string &className,
                           WorldObject2d &bodyA,
                           WorldObject2d &bodyB,
                           b2Joint *joint)
    : filing::NamedStoredObject(name, className),
      _joint(joint), _bodyA(bodyA), _bodyB(bodyB)
{
    _joint->SetUserData(this);
}

WorldJoint2d::WorldJoint2d(const filing::JsonIO &input,
                           WorldObject2d &bodyA,
                           WorldObject2d &bodyB,
                           b2Joint *joint)
    : filing::NamedStoredObject(input),
      _joint(joint), _bodyA(bodyA), _bodyB(bodyB)
{
    _joint->SetUserData(this);
}

WorldJoint2d &WorldJoint2d::getNext()
{
    return *static_cast<WorldJoint2d *>(_joint->GetNext()->GetUserData());
}

const WorldJoint2d &WorldJoint2d::getNext() const
{
    return *static_cast<WorldJoint2d *>(_joint->GetNext()->GetUserData());
}

b2Body *WorldJoint2d::getB2Body(WorldObject2d &obj) const
{
    return obj._body;
}

b2Joint *WorldJoint2d::getB2Joint(WorldJoint2d &joint) const
{
    return joint._joint;
}

void WorldJoint2d::initB2Joint(WorldLayer2d &layer, b2JointDef *jointDef)
{
    _joint = layer.addWorldJoint(std::shared_ptr<WorldJoint2d>(this), jointDef);
}

ample::graphics::Vector2d<float> WorldJoint2d::getAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldJoint2d::getAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldJoint2d::getReactionForce(float inv_dt) const
{
    const b2Vec2 &force = _joint->GetReactionForce(inv_dt);
    return {force.x, force.y};
}

float WorldJoint2d::getReactionTorque(float inv_dt) const
{
    return _joint->GetReactionTorque(inv_dt);
}

WorldObject2d &WorldJoint2d::getBodyA()
{
    return _bodyA;
}

WorldObject2d &WorldJoint2d::getBodyB()
{
    return _bodyB;
}

bool WorldJoint2d::isEnabled() const
{
    return _joint->IsEnabled();
}

bool WorldJoint2d::getCollideConnected() const
{
    return _joint->GetCollideConnected();
}

std::string WorldJoint2d::dump()
{
    filing::JsonIO output = NamedStoredObject::dump();
    output.write<std::string>("bodyA_name", _bodyA.name());
    output.write<std::string>("bodyB_name", _bodyB.name());
    return output;
}
} // namespace ample::physics