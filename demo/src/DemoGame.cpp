#include "DemoGame.h"
#include "ScreenCamera.h"
#include "Clock.h"

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
    this->_window.swapBuffer();
}
