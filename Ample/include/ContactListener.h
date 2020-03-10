#pragma once

#include "WorldObject2d.h"
#include "box2d/b2_world_callbacks.h"

namespace ample::physics
{
class Fixture;
class ContactListener : public b2ContactListener
{
public:
    virtual void startContact(Fixture &fixtureA, Fixture &fixtureB) = 0;
    virtual void endContact(Fixture &fixtureA, Fixture &fixtureB) = 0;

private:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
};
} // namespace ample::physics
