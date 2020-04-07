#include "WorldContact2d.h"

namespace ample::physics
{
WorldContact2d::WorldContact2d(b2Contact *contact)
    : _contact(contact) {}

b2Manifold *WorldContact2d::getManifold()
{
    return _contact->GetManifold();
}

const b2Manifold *WorldContact2d::getManifold() const
{
    return _contact->GetManifold();
}

void WorldContact2d::getWorldManifold(b2WorldManifold *worldManifold) const
{
    _contact->GetWorldManifold(worldManifold);
}

bool WorldContact2d::isTouching() const
{
    return _contact->IsTouching();
}

void WorldContact2d::setEnabled(bool flag)
{
    _contact->SetEnabled(flag);
}

bool WorldContact2d::isEnabled() const
{
    return _contact->IsEnabled();
}

WorldContact2d WorldContact2d::getNext()
{
    return {_contact->GetNext()};
}

Fixture WorldContact2d::getFixtureA()
{
    return {_contact->GetFixtureA()};
}

Fixture WorldContact2d::getFixtureB()
{
    return {_contact->GetFixtureB()};
}

void WorldContact2d::setFriction(float friction)
{
    _contact->SetFriction(friction);
}

float WorldContact2d::getFriction() const
{
    return _contact->GetFriction();
}

void WorldContact2d::resetFriction()
{
    _contact->ResetFriction();
}

void WorldContact2d::setRestitution(float restitution)
{
    _contact->SetRestitution(restitution);
}

float WorldContact2d::getRestitution() const
{
    return _contact->GetRestitution();
}

void WorldContact2d::resetRestitution()
{
    _contact->ResetRestitution();
}

void WorldContact2d::setTangentSpeed(float speed)
{
    _contact->SetTangentSpeed(speed);
}

float WorldContact2d::getTangentSpeed() const
{
    return _contact->GetTangentSpeed();
}

WorldContactEdge2d::WorldContactEdge2d(b2ContactEdge *contactEdge)
    : _contactEdge(contactEdge) {}

WorldObject2d &WorldContactEdge2d::getOther()
{
    return *static_cast<WorldObject2d *>(_contactEdge->other->GetUserData());
}

WorldContact2d WorldContactEdge2d::getContact()
{
    return {_contactEdge->contact};
}

WorldContactEdge2d WorldContactEdge2d::getPrev()
{
    return {_contactEdge->next};
}

WorldContactEdge2d WorldContactEdge2d::getNext()
{
    return {_contactEdge->prev};
}
} // namespace ample::physics