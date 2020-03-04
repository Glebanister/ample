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

void WorldLayer2d::onActive()
{
    graphics::Layer::onActive();
    world.Step(1.0 / time::Clock::getFPS(), 8, 3);
    auto bl = world.GetBodyList();
    static bool flag = true;
    if (flag)
    {
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1.0f, 1.0f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        bl->CreateFixture(&fixtureDef);
        flag = false;
    }
}

void WorldLayer2d::loadScene(const filing::Scene2d &scene)
{
    DEBUG("Stub for worldLayer load from scene");
    for (auto [id, obj] : scene.storage_)
    {
        addObject(*dynamic_cast<WorldObject2d*>(obj.get()));
    }
}
} // namespace ample::physics
