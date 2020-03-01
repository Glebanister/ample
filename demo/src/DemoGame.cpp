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
    addActivity(cameraBeh);
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_LEFT))
    {
        brick->_body->ApplyLinearImpulseToCenter({-100, 0}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_RIGHT))
    {
        brick->_body->ApplyLinearImpulseToCenter({100, 0}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        brick->_body->ApplyLinearImpulseToCenter({0, 100}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        brick->_body->ApplyLinearImpulseToCenter({0, -100}, true);
    }
}
