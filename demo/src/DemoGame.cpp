#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"
#include "WorldObject2d.h"
#include <memory>

DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    ample::physics::DefWorldObject2d groundBodyDef;
    groundBodyDef.setPosition({0.0f, -70.0f});
    ample::physics::DefWorldObject2d dynamicBodyDef;
    dynamicBodyDef.setBodyType(ample::physics::BodyType::dynamicBody);
    dynamicBodyDef.setPosition({0.0f, 100.0f});
    std::cerr << "DemoGame.cpp 18" << std::endl;
    ground = std::make_shared<ample::physics::WorldObject2d>(groundBodyDef,
                                                             (std::vector<ample::graphics::Vector2d<double>>){
                                                                 {-50, -50},
                                                                 {-50, 50},
                                                                 {50, 50},
                                                                 {50, -50},
                                                             });
    brick = std::make_shared<ample::physics::WorldObject2d>(dynamicBodyDef,
                                                            (std::vector<ample::graphics::Vector2d<double>>){
                                                                {-25, -25},
                                                                {-25, 25},
                                                                {25, 25},
                                                                {25, -25},
                                                            });
    brick->setColor256(255, 100, 100);

    worldLayer.addObject(*brick);
    worldLayer.addObject(*ground);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    std::cerr << "DemoGame.cpp 39" << std::endl;
}

void DemoGame::onAwake()
{
    LayeredWindowActivity::onAwake();
    std::cerr << "DemoGame.cpp 45" << std::endl;
}

void DemoGame::onActive()
{
    std::cerr << "DemoGame.cpp 50" << std::endl;
    LayeredWindowActivity::onActive();
    std::cerr << "DemoGame.cpp 52" << std::endl;
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_q))
    {
        brick->_body->ApplyForceToCenter({10000, 0}, false);
    }
    std::cerr << "DemoGame.cpp 57" << std::endl;
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        camera.translate(0, -10, 0);
    }
    std::cerr << "DemoGame.cpp 62" << std::endl;
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        camera.translate(0, 10, 0);
    }
    std::cerr << "DemoGame.cpp 67" << std::endl;
    std::cout << ample::time::Clock::getFPS() << std::endl;
    std::cerr << "DemoGame.cpp 69" << std::endl;
}
