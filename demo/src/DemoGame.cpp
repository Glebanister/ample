#include "DemoGame.h"
#include "ScreenCamera.h"
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
    static double speed = 3000.0;
    object.setX(1000.0 * (xNoise.noise0_1(ample::time::Clock::globalTimeMs() / speed) - 0.5));
    object.setY(1000.0 * (yNoise.noise0_1(ample::time::Clock::globalTimeMs() / speed) - 0.5));
    if (eventManager->keyIsDown(ample::control::keysym::ARROW_UP))
    {
        speed += 100;
    }
    if (eventManager->keyIsDown(ample::control::keysym::ARROW_DOWN))
    {
        speed -= 100;
    }
}
