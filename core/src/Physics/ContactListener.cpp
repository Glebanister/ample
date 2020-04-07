#include "ContactListener.h"
#include "box2d/b2_contact.h"
#include "Debug.h"

namespace ample::physics
{
void ContactListener::BeginContact(b2Contact *contact)
{
    startContact({contact});
}

void ContactListener::EndContact(b2Contact *contact)
{
    endContact({contact});
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    preSolve({contact}, oldManifold);
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    postSolve({contact}, impulse);
}

void ContactListener::startContact(WorldContact2d contact)
{
    (void)contact;
}
void ContactListener::endContact(WorldContact2d contact)
{
    (void)contact;
}
void ContactListener::preSolve(WorldContact2d contact, const b2Manifold *oldManifold)
{
    (void)contact;
    (void)oldManifold;
}
void ContactListener::postSolve(WorldContact2d contact, const b2ContactImpulse *impulse)
{
    (void)contact;
    (void)impulse;
}
} // namespace ample::physics
