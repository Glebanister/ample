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

// b2Body *WorldLayer2d::addWorldObject(std::shared_ptr<WorldObject2d> obj, b2BodyDef *bodyDef)
// {
//     graphics::Layer::addObject(std::static_pointer_cast<graphics::GraphicalObject>(obj));
//     _bodies.push_back(obj);
//     return world.CreateBody(bodyDef);
// }

void ample::physics::WorldLayer2d::addWorldObject(std::shared_ptr<ample::physics::WorldObject2d> obj)
{
    graphics::Layer::addObject(std::static_pointer_cast<graphics::GraphicalObject>(obj));
    _bodies.push_back(obj);
    obj->_body = world.CreateBody(&obj->_bodyDef);
}

b2Joint *WorldLayer2d::addWorldJoint(std::shared_ptr<WorldJoint2d> joint, b2JointDef *jointDef)
{
    _joints.push_back(joint);
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
