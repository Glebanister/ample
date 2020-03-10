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
    ample::physics::DefWorldObject2d groundBodyDef;
    groundBodyDef.setPosition({0.0f, 0.0f});
    ample::physics::DefWorldObject2d dynamicBodyDef;
    dynamicBodyDef.setBodyType(ample::physics::BodyType::dynamicBody);
    dynamicBodyDef.setPosition({0.0f, 0.0f});
    ground = std::make_shared<ample::physics::WorldObject2d>(groundBodyDef,
                                                             (std::vector<ample::graphics::Vector2d<float>>){
                                                                 {-70, -65.0},
                                                                 {-70, -25.0},
                                                                 {70, -60.0},
                                                                 {70, -70.0}});
    brick = std::make_shared<ample::physics::WorldObject2d>(dynamicBodyDef,
                                                            ample::geometry::RegularPolygon<float>(7.0, 6));
    worldLayer.addWorldObject(*brick);
    worldLayer.addWorldObject(*ground);
    auto brickFixture = brick->addFixture(ample::geometry::RegularPolygon<float>(7.0, 8));
    auto groundFixture = ground->addFixture({{-70, -65.0},
                                             {-70, -25.0},
                                             {70, -60.0},
                                             {70, -70.0}});
    groundFixture->setDensity(0.0f);
    groundFixture->setFriction(0.0f);
    brick->_body->SetAwake(true);
    brickFixture->setDensity(0.0);
    brickFixture->setFriction(0.0);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    b2MassData d;
    brick->_body->GetMassData(&d);
    d.I = 1;
    brick->_body->SetMassData(&d);
    addBehaviour(cameraBeh);
    ground->setFaceColor256({40, 155, 80});
    brick->setFaceColor256(0xbbbbbb);
    ground->setSideColor256({20, 100, 70});
    brick->setFaceColor256(0xbbbbbb);
    camera.translateEye({0, 0, -100});
    camera.translate({0, -30, 0});
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
}
