#include "WorldLayer2d.h"
#include "Clock.h"
#include "box2d/b2_polygon_shape.h"

namespace ample::physics
{
WorldLayer2d::WorldLayer2d(const graphics::Vector2d<float> &gravity) : world(b2Vec2(gravity.x, gravity.y)) {}

void WorldLayer2d::addObject(WorldObject2d &object)
{
    graphics::Layer::addObject(object);
    object._body = world.CreateBody(&(object._bodyDef));
}

void WorldLayer2d::onActive()
{
    graphics::Layer::onActive();
    world.Step(1.0 / 62.5, 8, 3);
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
    // std::cout << bl->GetPosition().x << ' ' << time::Clock::deltaTimeMs() << ' ' << bl->GetPosition().y << std::endl;
}
} // namespace physics
