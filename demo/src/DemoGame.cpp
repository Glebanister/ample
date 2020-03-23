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
    /*ground = &worldLayer.addWorldObject((std::vector<ample::graphics::Vector2d<float>>){
                                                                 {-70, -65.0},
                                                                 {-70, -25.0},
                                                                 {70, -60.0},
                                                                 {70, -70.0}}, {0, 0});
*/
    brick1 = &worldLayer.addWorldObject(ample::geometry::RegularPolygon<float>(7.0, 30),
                                        {0, -40}, ample::physics::BodyType::DYNAMIC_BODY);
    brick2 = &worldLayer.addWorldObject(ample::geometry::RegularPolygon<float>(7.0, 30),
                                        {0, -80});
    ground2 = &worldLayer.addWorldObject(ample::geometry::RegularPolygon<float>(7.0, 30),
                                        {80, -80});
    brick3 = &worldLayer.addWorldObject(ample::geometry::RegularPolygon<float>(7.0, 30),
                                        {0, 0}, ample::physics::BodyType::DYNAMIC_BODY);
    brick1->setAwake(false);
    brick2->setAwake(false);
    auto &brick1Fixture = brick1->addFixture(ample::geometry::RegularPolygon<float>(7.0, 7));
    /*auto& groundFixture = ground->addFixture({{-70, -65.0},
                                             {-70, -25.0},
                                             {70, -60.0},
                                             {70, -70.0}});*/
    auto &brick2Fixture = brick2->addFixture(ample::geometry::RegularPolygon<float>(7.0, 7));
    auto &brick3Fixture = brick3->addFixture(ample::geometry::RegularPolygon<float>(7.0, 7));
    auto &ground2Fixture = brick3->addFixture(ample::geometry::RegularPolygon<float>(7.0, 7));
    //auto brickFixture2 = brick->addFixture({{0, 0}, {10.0, 0}, {10.0, -2.0}, {0.0, -2.0}});
    //groundFixture.setDensity(1.0f);
    //groundFixture.setFriction(0.2f);
    //brick->setAwake(true);
    brick1Fixture.setDensity(1.0);
    brick1Fixture.setFriction(1.0);
    ground2Fixture.setDensity(1.0);
    ground2Fixture.setFriction(1.0);
    brick3Fixture.setDensity(1.0);
    brick3Fixture.setFriction(1.0);
    brick2Fixture.setDensity(1.0);
    brick2Fixture.setFriction(1.0);
    ample::physics::WorldDistanceJoint2d &q = dynamic_cast<ample::physics::WorldDistanceJoint2d &>(
                        worldLayer.addWorldDistanceJoint(*brick1, *brick2, 
                        brick1->getWorldCenter(), brick2->getWorldCenter()));
    ample::physics::WorldDistanceJoint2d &q2 = dynamic_cast<ample::physics::WorldDistanceJoint2d &>(
                        worldLayer.addWorldDistanceJoint(*brick1, *brick3, 
                        brick1->getWorldCenter(), brick3->getWorldCenter()));
    ample::physics::WorldDistanceJoint2d &q3 = dynamic_cast<ample::physics::WorldDistanceJoint2d &>(
                        worldLayer.addWorldDistanceJoint(*ground2, *brick3, 
                        ground2->getWorldCenter(), brick3->getWorldCenter()));
    //brickFixture2.setDensity(1.0);
    //brickFixture2.setFriction(1.0);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    ample::physics::MassData d;
    d = brick1->getMassData();
    d.I = 1;
    brick1->setMassData(d);
    //ground->setFaceColor256({20, 100, 70});
    brick1->setFaceColor256(0x964B00);
    q.setFaceColor256(0xff69b4);
    q2.setFaceColor256(0xff69b4);
    q3.setFaceColor256(0xff69b4);
    //q.setLength(20);
    //ground->setSideColor256({20, 100, 70});
    brick3->setFaceColor256(0x964B00);
    _window.disableCursor();
    worldLayer.addObject(lamp);
    lamp.translate({0, -10, -140});
    camera.translate({0, -10, -140});
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
