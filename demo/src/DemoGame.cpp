#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"
#include "WorldObject2d.h"
#include "Debug.h"
#include "RegularPolygon.h"
#include <memory>
#include <vector>

#include <fstream>
#include <sstream>

void MyContactListener::startContact(ample::physics::Fixture &fixtureA, ample::physics::Fixture &fixtureB)
{
   /* ample::physics::WorldObject2d *bodyA = &fixtureA.getObject();
    std::cout << bodyA << std::endl;
    ample::physics::WorldObject2d *bodyB = &fixtureB.getObject();*/
    //if (bodyA->id != 1)
    //    std::swap(bodyA, bodyB);
    //bodyA->_body->SetAngularVelocity(10);
    DEBUG("How are you?");
    //b2Vec2 imp;
    // if (bodyA->getX() < bodyB->getX())
    //     imp.x = -1000;
    // else
    //     imp.x = 1000;
    /*if (bodyA->getY() < bodyB->getY())
        imp.y = -1000;
    else
        imp.y = 1000;
    bodyA->_body->ApplyLinearImpulseToCenter(imp, true);*/
}
void MyContactListener::endContact(ample::physics::Fixture &fixtureA, ample::physics::Fixture &fixtureB) {}

DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    //worldLayer.setContactListener(listener);
    ground = worldLayer.addObject((std::vector<ample::graphics::Vector2d<double>>){
        {-70, -5.0},
        {-70, 5.0},
        {70, 0.0},
        {70, -10.0}}, {0.0, -1.0});
    brick = worldLayer.addObject((std::vector<ample::graphics::Vector2d<double>>){
        {-5, -5},
        {-5, 5},
        {5, 5},
        {5, -5}},
                                 {0, 0}, ample::physics::BodyType::DYNAMIC_BODY);
    brick->setColor256(255, 100, 100);
    intoBrick = brick->addSubShape((std::vector<ample::graphics::Vector2d<double>>){
        {-2.5, -2.5},
        {-2.5, 2.5},
        {2.5, 2.5},
        {2.5, -2.5}});
    intoBrick->setColor256(100, 256, 100);
    auto brickFixture = brick->addFixture(ample::geometry::RegularPolygon(7.0, 8));
    auto groundFixture = ground->addFixture({{-70, -5.0}, {-70, 5.0}, {70, 0.0}, {70, -10.0}});
    groundFixture->setDensity(0.5);
    groundFixture->setFriction(0);
    brick->setAwake(true);
    brickFixture->setDensity(1.0);
    brickFixture->setFriction(0.3);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    ample::physics::MassData d;
    d = brick->getMassData();
    d.I = 1;
    brick->setMassData(d);
    DEBUG(d.I);

    addActivity(cameraBeh);
    brick->setRatio(10);
    intoBrick->setRatio(10);
    ground->setRatio(10);
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::ARROW_LEFT))
    {
        auto vel = brick->getLinearVelocity();
        float desiredVel = 0;
        desiredVel = -10;
        float velChange = desiredVel - vel.x;
        float force = brick->getMass() * velChange / (1 / 60.0); //f = mv/t
        brick->applyForceToCenter({force, 0}, true);
    }
    if (eventManager->keyboard()->isKeyReleased(ample::control::keysym::ARROW_LEFT))
    {
        auto vel = brick->getLinearVelocity();
        float desiredVel = 0;
        desiredVel = 0;
        float velChange = desiredVel - vel.x;
        float force = brick->getMass() * velChange / (1 / 60.0); //f = mv/t
        brick->applyForceToCenter({force, 0}, true);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::ARROW_RIGHT))
    {
        auto vel = brick->getLinearVelocity();
        float desiredVel = 0;
        desiredVel = 10;
        float velChange = desiredVel - vel.x;
        float force = brick->getMass() * velChange / (1 / 60.0); //f = mv/t
        brick->applyForceToCenter({force, 0}, true);
    }
    if (eventManager->keyboard()->isKeyReleased(ample::control::keysym::ARROW_RIGHT))
    {
        auto vel = brick->getLinearVelocity();
        float desiredVel = 0;
        desiredVel = 0;
        float velChange = desiredVel - vel.x;
        float force = brick->getMass() * velChange / (1 / 60.0); //f = mv/t
        brick->applyForceToCenter({force, 0}, true);
    }
    if (eventManager->keyboard()->isKeyReleased(ample::control::keysym::ARROW_UP))
    {
        brick->applyLinearImpulseToCenter({0, 100}, true);
    }

    if (eventManager->keyboard()->isKeyReleased(ample::control::keysym::ARROW_DOWN))
    {
        brick->applyLinearImpulseToCenter({0, -100}, true);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::SPACE))
    {
        brick->setAngularVelocity(4);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::KEY_b))
    {
        brick->setAwake(false);
    }
    camera.look();
    ample::graphics::ScreenObject circle{ample::geometry::RegularPolygon<int>(50, 10)};
    circle.setColor256(100, 200, 100);
    circle.draw();
    camera.unlook();
}
