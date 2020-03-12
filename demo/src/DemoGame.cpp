#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"
#include "WorldObject2d.h"
#include "Debug.h"
#include "RegularPolygon.h"
#include "CameraBehavior.h"
#include <memory>
#include <vector>

#include <fstream>
#include <sstream>


void MyContactListener::startContact(ample::physics::Fixture &fixtureA, ample::physics::Fixture &fixtureB)
{
    ample::physics::WorldObject2d *bodyA = &fixtureA.getObject();
    ample::physics::WorldObject2d *bodyB = &fixtureB.getObject();
}

void MyContactListener::endContact(ample::physics::Fixture &fixtureA, ample::physics::Fixture &fixtureB) {}

DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    worldLayer.setContactListener(listener);
    ground = &worldLayer.addWorldObject((std::vector<ample::graphics::Vector2d<float>>){
                                                                 {-70, -65.0},
                                                                 {-70, -25.0},
                                                                 {70, -60.0},
                                                                 {70, -70.0}}, {0, 0});

    brick = &worldLayer.addWorldObject(ample::geometry::RegularPolygon<float>(7.0, 7),
                                      {0, 0}, ample::physics::BodyType::DYNAMIC_BODY);

    auto brickFixture = brick->addFixture(ample::geometry::RegularPolygon<float>(7.0, 7));
    auto groundFixture = ground->addFixture({{-70, -65.0},
                                             {-70, -25.0},
                                             {70, -60.0},
                                             {70, -70.0}});
    groundFixture.setDensity(1.0f);
    groundFixture.setFriction(0.2f);
    brick->setAwake(true);
    brickFixture.setDensity(1.0);
    brickFixture.setFriction(1.0);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    ample::physics::MassData d;
    d = brick->getMassData();
    d.I = 1;
    brick->setMassData(d);
    ground->setFaceColor256({20, 100, 70});
    brick->setFaceColor256(0x964B00);
    ground->setSideColor256({20, 100, 70});
    brick->setFaceColor256(0x964B00);
    _window.disableCursor();
    worldLayer.addObject(lamp);
    lamp.translate({0, -10, -140});
    camera.translate({0, -10, -140});
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        lamp.translate({-1, 0, 0});
        camera.translate({-1, 0, 0});
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        lamp.translate({1, 0, 0});
        camera.translate({1, 0, 0});
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        lamp.translate({0, 1, 0});
        camera.translate({0, 1, 0});
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        lamp.translate({0, -1, 0});
        camera.translate({0, -1, 0});
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_w))
    {
        lamp.translate({0, 0, 1});
        camera.translate({0, 0, 1});
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_s))
    {
        lamp.translate({0, 0, -1});
        camera.translate({0, 0, -1});
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_LEFT))
    {
        lamp.rotate({0, 1, 0}, 1.0);
        camera.rotate({0, 1, 0}, 1.0);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_RIGHT))
    {
        lamp.rotate({0, 1, 0}, -1.0);
        camera.rotate({0, 1, 0}, -1.0);
    }
}
