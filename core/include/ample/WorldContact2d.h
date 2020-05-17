#pragma once

#include "box2d/b2_contact.h"
#include "WorldObject2d.h"

namespace ample::physics
{
class Fixture;
class WorldObject2d;
class WorldContact2d
{
public:
    b2Manifold *getManifold();
    const b2Manifold *getManifold() const;

    void getWorldManifold(b2WorldManifold *worldManifold) const;

    bool isTouching() const;

    void setEnabled(bool flag);

    bool isEnabled() const;

    WorldContact2d getNext();

    Fixture getFixtureA();

    Fixture getFixtureB();

    //int32 GetChildIndexA() const;
    //int32 GetChildIndexB() const;

    void setFriction(float friction);

    float getFriction() const;

    void resetFriction();

    void setRestitution(float restitution);

    float getRestitution() const;

    void resetRestitution();

    void setTangentSpeed(float speed);

    float getTangentSpeed() const;

    WorldContact2d(b2Contact *contact);

private:
    b2Contact *_contact = nullptr;
};

class WorldContactEdge2d
{
public:
    WorldObject2d &getOther();
    WorldContact2d getContact();
    WorldContactEdge2d getPrev();
    WorldContactEdge2d getNext();

    operator bool();

private:
    friend WorldObject2d;

    WorldContactEdge2d(b2ContactEdge *contactEdge);
    b2ContactEdge *_contactEdge = nullptr;
};
} // namespace ample::physics