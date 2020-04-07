#pragma once

#include "WorldObject2d.h"
#include "WorldContact2d.h"
#include "box2d/b2_world_callbacks.h"

namespace ample::physics
{
class Fixture;
class WorldContact2d;
class ContactListener : public b2ContactListener
{
public:
    virtual void startContact(WorldContact2d contact);
    virtual void endContact(WorldContact2d contact);
    virtual void preSolve(WorldContact2d contact, const b2Manifold *oldManifold);
    virtual void postSolve(WorldContact2d contact, const b2ContactImpulse *impulse);

private:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;
};
} // namespace ample::physics
