#include "WorldLayer2d.h"
#include "Clock.h"
#include "box2d/b2_polygon_shape.h"

namespace ample::physics
{
WorldLayer2d::WorldLayer2d(const graphics::Vector2d<float> &gravity) : world(b2Vec2(gravity.x, gravity.y)) {}

void WorldLayer2d::addObject(std::shared_ptr<graphics::GraphicalObject> object)
{
    ample::graphics::Layer::addObject(object);
    ample::physics::WorldObject2d *worldObj = static_cast<WorldObject2d *>(object.get());
    worldObj->_body = world.CreateBody(&(worldObj->_bodyDef));
}

void WorldLayer2d::onActive()
{
    ample::graphics::Layer::onActive();
    world.Step(1.0 / 62.5, 8, 3);
    std::cout << time::Clock::getFPS() << std::endl;
    auto bl = world.GetBodyList();
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
} // namespace ample::physics