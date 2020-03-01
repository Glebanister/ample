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
    std::vector<ample::graphics::Vector2d<double>> shapeGround = {{-50, -50}, {-50, 50}, {50, 50}, {50, -50}};
    ground = std::make_shared<ample::physics::WorldObject2d>(groundBodyDef, shapeGround);
    worldLayer.addObject(ground);
    worldLayer.addCamera(std::make_shared<ample::graphics::CameraOrtho>(camera));
    ample::physics::DefWorldObject2d dynamicBodyDef;
    dynamicBodyDef.setBodyType(ample::physics::BodyType::dynamicBody);
    dynamicBodyDef.setPosition({0.0f, 100.0f});
    std::vector<ample::graphics::Vector2d<double>> shapeBrick = {{-25, -25}, {-25, 25}, {25, 25}, {25, -25}};
    brick = std::make_shared<ample::physics::WorldObject2d>(dynamicBodyDef, shapeBrick);
    worldLayer.addObject(brick);
    brick->setColor256(255, 100, 100);
    addLayer(std::make_shared<ample::physics::WorldLayer2d>(worldLayer));
}

void DemoGame::onAwake()
{
    LayeredWindowActivity::onAwake();
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_q))
    {
        brick->_body->ApplyForceToCenter({10000, 0}, false);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        camera.translate(0, -10, 0);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        camera.translate(0, 10, 0);
    }
    std::cout << ample::time::Clock::getFPS() << std::endl;
}
