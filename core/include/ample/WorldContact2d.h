#pragma once

#include "box2d/b2_contact.h"
#include "WorldObject2d.h"

namespace ample::physics
{
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
} // namespace ample::physics