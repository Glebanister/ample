#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::window::WindowActivity(window)
    {
        addActivity(cameraBeh);
    }

void DemoGame::onAwake()
{
    WindowActivity::onAwake();
    std::cout << getWidth() << ' ' << getHeight() << std::endl;
    current->setColor256(200, 100, 100);
    objectBig.translate(0, 0, -150);
    objectSmall.translate(0, 0, -150);
    _window.disableCursor();
}

void DemoGame::onActive()
{
    WindowActivity::onActive();
    camera.look();
    objectSmall.draw();
    objectBig.draw();
    camera.unlook();

    screenCamera.look();
    ample::graphics::ScreenObject({{-3, -3}, {3, -3}, {3, 3}, {-3, 3}}, {0, 0, 0}).draw();
    screenCamera.unlook();

    _window.moveCursor(0, 0);
}
