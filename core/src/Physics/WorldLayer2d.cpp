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
    ASSERT(0.0 <= _relativePositionInSlice && _relativePositionInSlice <= 1.0);
}

void WorldLayer2d::setContactListener(ContactListener &listener)
{
    world.SetContactListener(&listener);
}

b2Body *WorldLayer2d::addWorldObject(WorldObject2d &obj, b2BodyDef *bodyDef)
{
    graphics::Layer::addObject(obj);
    _bodies.push_back(&obj);
    return world.CreateBody(bodyDef);
}

b2Joint *WorldLayer2d::addWorldJoint(WorldJoint2d &joint, b2JointDef *jointDef)
{
    _joints.push_back(&joint);
    return world.CreateJoint(jointDef);
}

void WorldLayer2d::onActive()
{
    graphics::Layer::onActive();
    world.Step(1.0 / time::Clock::getFPS(), 8, 3);
}

float WorldLayer2d::getZ() const noexcept
{
    return _z;
}
float WorldLayer2d::getThickness() const noexcept
{
    return _thickness;
}
float WorldLayer2d::getRelativePositionInSlice() const noexcept
{
    return _relativePositionInSlice;
}
} // namespace ample::physics
