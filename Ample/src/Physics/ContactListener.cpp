#include "ContactListener.h"
#include "box2d/b2_contact.h"
#include "Debug.h"

namespace ample::physics
{
void ContactListener::BeginContact(b2Contact *contact)
{
    auto fixtureA = static_cast<Fixture *>(contact->GetFixtureA()->GetUserData());
    auto fixtureB = static_cast<Fixture *>(contact->GetFixtureB()->GetUserData());
    //check nullptr
    startContact(*fixtureA, *fixtureB);
}
void ContactListener::EndContact(b2Contact *contact)
{
    auto fixtureA = static_cast<Fixture *>(contact->GetFixtureA()->GetUserData());
    auto fixtureB = static_cast<Fixture *>(contact->GetFixtureB()->GetUserData());
    //check nullptr
    endContact(*fixtureA, *fixtureB);
}
} // namespace ample::physics
