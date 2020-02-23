#include "DemoGame.h"
#include "Clock.h"
#include "PerlinNoise.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::window::WindowActivity(window) {}

void DemoGame::onAwake()
{
    WindowActivity::onAwake();
    std::cout << getWidth() << ' ' << getHeight() << std::endl;
}

void DemoGame::onActive()
{
    WindowActivity::onActive();
    camera.look();
    objectBig.draw();
    objectSmall.draw();
    camera.unlook();
    if (eventManager->keyIsDown(ample::control::keysym::ARROW_LEFT))
    {
        camera.translate(-5, 0, 0);
    }
    else if (eventManager->keyIsDown(ample::control::keysym::ARROW_RIGHT))
    {
        camera.translate(5, 0, 0);
    }
    if (eventManager->keyIsDown(ample::control::keysym::ARROW_UP))
    {
        objectBig.translate(0, 0, 0.02);
    }
    if (eventManager->keyIsDown(ample::control::keysym::ARROW_DOWN))
    {
        objectBig.translate(0, 0, -0.02);
    }
}
