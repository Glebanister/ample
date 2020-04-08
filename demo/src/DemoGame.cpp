#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "DemoGame.h"
#include "RegularPolygon.h"
#include "Texture.h"
#include "Clock.h"
#include "KeyboardTransition.h"
#include "MouseTransition.h"
#include "TimerTransition.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::game::game2d::Game2d(window)
{
    auto level = createLevel(1, 10.0f, 0.5f);
    //level->frontSlice()->addObject(braid);
    rope = std::shared_ptr<Rope>(new Rope(level->frontSlice(), "rope",
                                          100, 2, 20,
                                          {0, 0},
                                          0.2f,
                                          1,
                                          {-80, 80},
                                          0));
    ball = std::shared_ptr<ample::physics::WorldObject2d>(new ample::physics::WorldObject2d("ball",
                                                                                            *(level->frontSlice()),
                                                                                            ample::physics::BodyType::DYNAMIC_BODY,
                                                                                            ample::geometry::RegularPolygon<float>(7, 30),
                                                                                            1.0,
                                                                                            {1.0f, 1.0f},
                                                                                            {1.0f, 1.0f},
                                                                                            ample::graphics::normalsMode::VERTEX,
                                                                                            rope->nodes.back()->getPosition()));
    level->frontSlice()->addWorldObject(ball);
    {
        auto fixture = ball->addFixture(ample::geometry::RegularPolygon<float>(7, 8));
        fixture.setDensity(1.0f);
        fixture.setFriction(1.0f);
    }
    ample::physics::MassData d = ball->getMassData();
    d.I = 1;
    d.mass = 1;
    ball->setMassData(d);
    ball->setGravityScale(-9);
    new ample::physics::WorldRevoluteJoint2d(*ball, *(rope->nodes.back()), rope->nodes.back()->getPosition());
    ground = std::shared_ptr<ample::physics::WorldObject2d>(new ample::physics::WorldObject2d("ground",
                                                                                              *(level->frontSlice()),
                                                                                              ample::physics::BodyType::STATIC_BODY,
                                                                                              {{30, 10}, {30, -5}, {-30, -5}, {-30, 2}},
                                                                                              1.0,
                                                                                              {1.0f, 1.0f},
                                                                                              {1.0f, 1.0f},
                                                                                              ample::graphics::normalsMode::VERTEX,
                                                                                              {-50, -50}));
    level->frontSlice()->addWorldObject(ground);
    auto fixture = ground->addFixture({{30, 10}, {30, -5}, {-30, -5}, {-30, 2}});
    fixture.setDensity(1.0f);
    fixture.setFriction(1.0f);
    fixed = std::shared_ptr<ample::physics::WorldObject2d>(new ample::physics::WorldObject2d("fixed",
                                                                                             *(level->frontSlice()),
                                                                                             ample::physics::BodyType::STATIC_BODY,
                                                                                             ample::geometry::RegularPolygon<float>(2, 30),
                                                                                             1.0,
                                                                                             {1.0f, 1.0f},
                                                                                             {1.0f, 1.0f},
                                                                                             ample::graphics::normalsMode::VERTEX,
                                                                                             {-50, 100}));
    level->frontSlice()->addWorldObject(fixed);
    fixture = fixed->addFixture(ample::geometry::RegularPolygon<float>(2, 8));
    fixture.setDensity(1.0f);
    fixture.setFriction(1.0f);
    ropeToHeavyBall = std::shared_ptr<Rope>(new Rope(level->frontSlice(), "ropeToHeavyBall",
                                                     110, 2, 40,
                                                     {-50, 100},
                                                     0.2,
                                                     5,
                                                     {-60, 60}));
    heavyBall = std::shared_ptr<ample::physics::WorldObject2d>(new ample::physics::WorldObject2d("heavyBall",
                                                                                                 *(level->frontSlice()),
                                                                                                 ample::physics::BodyType::DYNAMIC_BODY,
                                                                                                 ample::geometry::RegularPolygon<float>(7, 30),
                                                                                                 1.0,
                                                                                                 {1.0f, 1.0f},
                                                                                                 {1.0f, 1.0f},
                                                                                                 ample::graphics::normalsMode::VERTEX,
                                                                                                 {-50, -10}));
    level->frontSlice()->addWorldObject(heavyBall);
    fixture = heavyBall->addFixture(ample::geometry::RegularPolygon<float>(7, 8));
    fixture.setDensity(1.0f);
    fixture.setFriction(1.0f);
    d = heavyBall->getMassData();
    d.I = 1;
    d.mass = 4;
    heavyBall->setMassData(d);
    new ample::physics::WorldRevoluteJoint2d(*heavyBall, *(ropeToHeavyBall->nodes.back()), {-50, -10});

    box = std::shared_ptr<ample::physics::WorldObject2d>(new ample::physics::WorldObject2d("box",
                                                                                           *(level->frontSlice()),
                                                                                           ample::physics::BodyType::DYNAMIC_BODY,
                                                                                           {{8, 8}, {8, -8}, {-8, -8}, {-8, 8}},
                                                                                           1.0,
                                                                                           {1.0f, 1.0f},
                                                                                           {1.0f, 1.0f},
                                                                                           ample::graphics::normalsMode::VERTEX,
                                                                                           {-42, 10}));
    level->frontSlice()->addWorldObject(box);
    fixture = box->addFixture({{8, 8}, {8, -8}, {-8, -8}, {-8, 8}});
    fixture.setDensity(1.0f);
    fixture.setFriction(0.1f);
    d = box->getMassData();
    d.I = 1;
    d.mass = 6;
    box->setMassData(d);
    setCurrentLevel(1);
    level->camera()->translate({0.0, 10.0, 0.0});
    cameraRemote = std::make_shared<KeyboardControlCamera>(eventManager(), level->camera());
    addBehavior(std::static_pointer_cast<Behavior>(cameraRemote));
    level->frontSlice()->addObject(std::static_pointer_cast<ample::graphics::GraphicalObject>(cameraRemote->getLamp()));
}

void DemoGame::onActive()
{
    Game2d::onActive();
    if (eventManager().keyboard().isKeyDown(ample::control::keysym::KEY_h))
    {
        box->setSpeedX(-30);
    }
    if (eventManager().keyboard().isKeyDown(ample::control::keysym::KEY_f))
    {
        box->setSpeedX(30);
    }
     if (eventManager().keyboard().isKeyReleased(ample::control::keysym::KEY_t))
    {
        box->applyLinearImpulseToCenter({0, 100}, true);
    }
}
