#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_body.h"
#include "box2d/b2_joint.h"
#include "box2d/b2_distance_joint.h"

#include "WorldLayer2d.h"
#include "Clock.h"
#include "Exception.h"
#include "Debug.h"

namespace ample::physics
{
WorldLayer2d::WorldLayer2d(const graphics::Vector2d<float> &gravity,
                           float z,
                           float thickness,
                           float relativePositionInSlice)
    : world(b2Vec2(gravity.x, gravity.y)),
      _z(z),
      _thickness(thickness),
      _relativePositionInSlice(relativePositionInSlice)
{
}

void WorldLayer2d::setContactListener(ContactListener &listener)
{
    world.SetContactListener(&listener);
}

WorldContact2d WorldLayer2d::getContactList()
{
    return {world.GetContactList()};
}

void WorldLayer2d::clearForces()
{
    world.ClearForces();
}

WorldObject2d &WorldLayer2d::getBodyList()
{
    return *static_cast<WorldObject2d *>(world.GetBodyList()->GetUserData());
}

const WorldObject2d &WorldLayer2d::getBodyList() const
{
    return *static_cast<WorldObject2d *>(world.GetBodyList()->GetUserData());
}

WorldJoint2d &WorldLayer2d::getJointList()
{
    return *static_cast<WorldJoint2d *>(world.GetJointList()->GetUserData());
}

const WorldJoint2d &WorldLayer2d::getJointList() const
{
    return *static_cast<WorldJoint2d *>(world.GetJointList()->GetUserData());
}

void WorldLayer2d::setAllowSleeping(bool flag)
{
    world.SetAllowSleeping(flag);
}

bool WorldLayer2d::getAllowSleeping() const
{
    return world.GetAllowSleeping();
}

void WorldLayer2d::setGravity(const b2Vec2 &gravity)
{
    world.SetGravity(gravity);
}

b2Vec2 WorldLayer2d::getGravity() const
{
    return world.GetGravity();
}

bool WorldLayer2d::isLocked() const
{
    return world.IsLocked();
}

void WorldLayer2d::setAutoClearForces(bool flag)
{
    world.SetAutoClearForces(flag);
}

bool WorldLayer2d::getAutoClearForces() const
{
    return world.GetAutoClearForces();
}

void WorldLayer2d::shiftOrigin(const b2Vec2 &newOrigin)
{
    world.ShiftOrigin(newOrigin);
}

b2Body *WorldLayer2d::addWorldObject(WorldObject2d &obj, b2BodyDef *bodyDef)
{
    graphics::Layer::addObject(obj);
    _bodies.push_back(&obj);
    return world.CreateBody(bodyDef);
}

b2Joint *WorldLayer2d::addWorldJoint(WorldJoint2d &joint, b2JointDef *jointDef)
{
    addBehaviour(joint);
    _joints.push_back(&joint);
    return world.CreateJoint(jointDef);
}

void WorldLayer2d::onActive()
{
    graphics::Layer::onActive();
    world.Step(1.0 / time::Clock::getFPS(), 8, 3);
}
} // namespace ample::physics
