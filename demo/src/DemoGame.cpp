#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"
#include "WorldObject2d.h"
#include "WorldDistanceJoint.h"
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
    //bodyA->applyImpulsToCenter({-100, 0.}, true);
    //bodyA->setAngularVelocity(4.0);
    //bodyB->applyImpulsToCenter({-100, 0.}, true);
    //bodyB->setAngularVelocity(4.0);
}

void MyContactListener::endContact(ample::physics::Fixture &fixtureA, ample::physics::Fixture &fixtureB) {}

DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    worldLayer.setContactListener(listener);
    ample::physics::DefWorldObject2d groundBodyDef;
    groundBodyDef.setPosition({0.0f, 0.0f});
    ample::physics::DefWorldObject2d dynamicBodyDef;
    dynamicBodyDef.setBodyType(ample::physics::BodyType::dynamicBody);
    dynamicBodyDef.setPosition({0.0f, 3.0f});
    ground = std::make_shared<ample::physics::WorldObject2d>(groundBodyDef,
                                                             (std::vector<ample::graphics::Vector2d<double>>){
                                                                 {-7, -0.2},
                                                                 {-7, 0.9},
                                                                 {7, 0.0},
                                                                 {7, -0.2},
                                                             });
    brick = std::make_shared<ample::physics::WorldObject2d>(dynamicBodyDef,
                                                            ample::geometry::RegularPolygon(0.7, 50));
    brick->setColor256(255, 100, 100);
    worldLayer.addObject(*brick);
    worldLayer.addObject(*ground);
    auto brickFixture = brick->addFixture(ample::geometry::RegularPolygon(0.7, 8));
    auto groundFixture = ground->addFixture({
        {-7, -0.2},
        {-7, 0.9},
        {7, 0.0},
        {7, -0.2},
    });
    groundFixture->setDensity(0.8);
    groundFixture->setFriction(0);
    brick->_body->SetAwake(true);
    brickFixture->setDensity(1.0);
    brickFixture->setFriction(0.1);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    ample::physics::MassData d;
    d = brick1->getMassData();
    d.I = 1;
    brick->_body->SetMassData(&d);

    addActivity(cameraBeh);
    brick->setRatio(120);
    ground->setRatio(120);
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_g))
    {
        brick1->applyForceToCenter({10000, 0}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_f))
    {
        brick1->applyForceToCenter({-100, 0}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_r))
    {
        brick2->applyForceToCenter({0, -100}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        lamp.translate({-1, 0, 0});
        camera.translate({-1, 0, 0});
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        brick->_body->ApplyLinearImpulseToCenter(b2Vec2(0, 5), true);
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
        brick->_body->ApplyLinearImpulseToCenter(b2Vec2(0, -5), true);
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
