#include "WorldLayer2d.h"
#include "Clock.h"

namespace ample::physics
{
WorldLayer2d::WorldLayer2d(const graphics::Vector2d<float> &gravity) : world(b2Vec2(gravity.x, gravity.y)) {}

void WorldLayer2d::addObject(std::shared_ptr<graphics::GraphicalObject> object)
{
    ample::graphics::Layer::addObject(object);
    ample::physics::WorldObject2d *worldObj = static_cast<WorldObject2d *>(object.get());
    worldObj->_body = world.CreateBody(&(worldObj->_bodyDef));
}

void WorldLayer2d::onActive() {
    ample::graphics::Layer::onActive();
    world.Step(time::Clock::deltaTimeMs(), 8, 3);
}
} // namespace ample::physics