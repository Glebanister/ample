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
    /*graphics::Layer::addObject(object);
    object._body = world.CreateBody(&(object._bodyDef));*/
}

std::shared_ptr<WorldObject2d> WorldLayer2d::addObject(const std::vector<ample::graphics::Vector2d<double>> &shape,
                                                      ample::graphics::Vector2d<float> pos,
                                                      BodyType type, float angle)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.angle = angle;
    switch (type)
    {
    case BodyType::STATIC_BODY:
        bodyDef.type = b2_staticBody;
        break;
    case BodyType::KINEMATIC_BODY:
        bodyDef.type = b2_kinematicBody;
        break;
    case BodyType::DYNAMIC_BODY:
        bodyDef.type = b2_dynamicBody;
        break;
    }
    bodies.emplace_back(new WorldObject2d(world.CreateBody(&bodyDef), shape));
    graphics::Layer::addObject(*(bodies[bodies.size() - 1]));
    return bodies[bodies.size() - 1];
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
    DEBUG("Stub for worldLayer load from scene");
    for (auto [id, obj] : scene.storage_)
    {
        addObject(*dynamic_cast<WorldObject2d *>(obj.get()));
    }
}
} // namespace ample::physics
