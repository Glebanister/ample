#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"
#include "WorldObject2d.h"
#include "RegularPolygon.h"
#include <memory>

#include <fstream>
#include <sstream>

DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    worldLayer.loadScene(firstScene);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    addActivity(cameraBeh);
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    auto brick = static_cast<ample::physics::WorldObject2d &>(firstScene.getElementById(1));
    auto ground = static_cast<ample::physics::WorldObject2d &>(firstScene.getElementById(2));
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_LEFT))
    {
        brick._body->ApplyLinearImpulseToCenter({-100, 0}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_RIGHT))
    {
        brick._body->ApplyLinearImpulseToCenter({100, 0}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        brick._body->ApplyLinearImpulseToCenter({0, 100}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        brick._body->ApplyLinearImpulseToCenter({0, -100}, true);
    }
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::SPACE))
    {
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
}
