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
    ample::physics::WorldObject2d *bodyA = &fixtureA.getObject();
    std::cout << bodyA << std::endl;
    ample::physics::WorldObject2d *bodyB = &fixtureB.getObject();
    if (bodyA->id != 1)
        std::swap(bodyA, bodyB);
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
    worldLayer.setContactListener(listener);
    ample::physics::DefWorldObject2d groundBodyDef;
    groundBodyDef.setPosition({0.0f, 0.0f});
    ample::physics::DefWorldObject2d dynamicBodyDef;
    dynamicBodyDef.setBodyType(ample::physics::BodyType::dynamicBody);
    dynamicBodyDef.setPosition({0.0f, 0.0f});
    ground = std::make_shared<ample::physics::WorldObject2d>(groundBodyDef,
                                                             (std::vector<ample::graphics::Vector2d<double>>){
                                                                 {-70, -5.0},
                                                                 {-70, 5.0},
                                                                 {70, 0.0},
                                                                 {70, -10.0}});
    brick = std::make_shared<ample::physics::WorldObject2d>(dynamicBodyDef,
                                                            (std::vector<ample::graphics::Vector2d<double>>){
                                                                {-2.5, -2.5},
                                                                {-2.5, 2.5},
                                                                {2.5, 2.5},
                                                                {2.5, -2.5},
                                                            });
    brick->setColor256(255, 100, 100);
    ground->id = 0;
    brick->id = 1;
    worldLayer.addObject(*brick);
    worldLayer.addObject(*ground);
    auto brickFixture = brick->addFixture({{-2.5, -2.5}, {-2.5, 2.5}, {2.5, 2.5}, {2.5, -2.5}});
    auto groundFixture = ground->addFixture({{-70, -5.0}, {-70, 5.0}, {70, 0.0}, {70, -10.0}});
    groundFixture->setDensity(0.5);
    groundFixture->setFriction(0.3);
    brick->_body->SetAwake(true);
    brickFixture->setDensity(1.0);
    brickFixture->setFriction(0.3);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    b2MassData d;
    brick->_body->GetMassData(&d);
    d.I = 1;
    brick->_body->SetMassData(&d);
    DEBUG(d.I);

    addActivity(cameraBeh);
    brick->setRatio(10);
    ground->setRatio(10);
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();

    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::ARROW_LEFT))
    {
        b2Vec2 vel = brick->_body->GetLinearVelocity();
        float desiredVel = 0;
        desiredVel = -10;
        float velChange = desiredVel - vel.x;
        float force = brick->_body->GetMass() * velChange / (1 / 60.0); //f = mv/t
        brick->_body->ApplyForceToCenter(b2Vec2(force, 0), true);
    }
    if (eventManager->keyboard()->isKeyReleased(ample::control::keysym::ARROW_LEFT))
    {
        b2Vec2 vel = brick->_body->GetLinearVelocity();
        float desiredVel = 0;
        desiredVel = 0;
        float velChange = desiredVel - vel.x;
        float force = brick->_body->GetMass() * velChange / (1 / 60.0); //f = mv/t
        brick->_body->ApplyForceToCenter(b2Vec2(force, 0), true);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::ARROW_RIGHT))
    {
        b2Vec2 vel = brick->_body->GetLinearVelocity();
        float desiredVel = 0;
        desiredVel = 10;
        float velChange = desiredVel - vel.x;
        float force = brick->_body->GetMass() * velChange / (1 / 60.0); //f = mv/t
        brick->_body->ApplyForceToCenter(b2Vec2(force, 0), true);
    }
    if (eventManager->keyboard()->isKeyReleased(ample::control::keysym::ARROW_RIGHT))
    {
        b2Vec2 vel = brick->_body->GetLinearVelocity();
        float desiredVel = 0;
    MS_STOP:
        desiredVel = 0;
        float velChange = desiredVel - vel.x;
        float force = brick->_body->GetMass() * velChange / (1 / 60.0); //f = mv/t
        brick->_body->ApplyForceToCenter(b2Vec2(force, 0), true);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::ARROW_UP))
    {
        auto t = brick->_body->GetLinearVelocity();
        t.y += 50;
        brick->_body->SetLinearVelocity(t);
    }
    if (eventManager->keyboard()->isKeyReleased(ample::control::keysym::ARROW_UP))
    {
        auto t = brick->_body->GetLinearVelocity();
        t.y -= 50;
        brick->_body->SetLinearVelocity(t);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::ARROW_DOWN))
    {
        auto t = brick->_body->GetLinearVelocity();
        t.y -= 50;
        brick->_body->SetLinearVelocity(t);
    }
    if (eventManager->keyboard()->isKeyReleased(ample::control::keysym::ARROW_DOWN))
    {
        auto t = brick->_body->GetLinearVelocity();
        t.x += 50;
        brick->_body->SetLinearVelocity(t);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::SPACE))
    {
<<<<<<< HEAD

        brick->_body->SetAngularVelocity(4);
        //isAng = true;
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::KEY_b))
    {
        brick->_body->SetAwake(false);
        //isAng = false;
    }
    // std::cout << brick->getX() << ' ' << brick->getY() << std::endl;
=======
        brick._body->SetAngularVelocity(4);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::KEY_b))
    {
        brick._body->SetAwake(false);
    }
    camera.look();
    ample::graphics::ScreenObject circle{ample::geometry::RegularPolygon<int>(50, 10)};
    circle.setColor256(100, 200, 100);
    circle.draw();
    camera.unlook();
>>>>>>> 60b7d8ea1662bcab87e483b07c7b7c55e748ff42
}
