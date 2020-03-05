#include "box2d/b2_polygon_shape.h"

#include "WorldLayer2d.h"
#include "Clock.h"
#include "Debug.h"

namespace ample::physics
{
WorldLayer2d::WorldLayer2d(const graphics::Vector2d<float> &gravity)
    : world(b2Vec2(gravity.x, gravity.y)) {}

void WorldLayer2d::addObject(WorldObject2d &object)
{
    graphics::Layer::addObject(object);
    object._body = world.CreateBody(&(object._bodyDef));
}

void WorldLayer2d::setContactListener(ContactListener &listener)
{
    world.SetContactListener(&listener);
}

void WorldLayer2d::onActive()
{
    graphics::Layer::onActive();
    world.Step(1.0 / time::Clock::getFPS(), 8, 3);
}

void WorldLayer2d::loadScene(const filing::Scene2d &scene)
{
    for (auto [id, obj] : scene.storage_)
    {
        addObject(*dynamic_cast<WorldObject2d *>(obj.get()));
    }
}
} // namespace ample::physics
