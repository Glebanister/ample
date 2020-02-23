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
    object.draw();
    camera.unlook();
    // static double speed = 3000.0;
    // object.setPosition((1000.0 * (xNoise.noise0_1(ample::time::Clock::globalTimeMs() / speed) - 0.5)),
    //                     1000.0 * (yNoise.noise0_1(ample::time::Clock::globalTimeMs() / speed) - 0.5),
    //                     object.getZ());
    if (eventManager->keyIsDown(ample::control::keysym::ARROW_UP))
    {
        object.rotate(0, 0, 1);
    }
    if (eventManager->keyIsDown(ample::control::keysym::ARROW_DOWN))
    {
        object.rotate(0, 0, -1);
    }
}
