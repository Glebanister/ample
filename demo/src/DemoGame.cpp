#include "DemoGame.h"
#include "Clock.h"
#include "PerlinNoise.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::window::WindowActivity(window) {}

void DemoGame::onAwake()
{
    WindowActivity::onAwake();
    std::cout << getWidth() << ' ' << getHeight() << std::endl;
    current->setColor256(200, 100, 100);
    objectBig.translate(0, 0, -150);
    objectSmall.translate(0, 0, -150);
}

void DemoGame::onActive()
{
    WindowActivity::onActive();
    camera.look();
    objectSmall.draw();
    objectBig.draw();
    camera.unlook();
    if (eventManager->keyboard()->isKeyPressed(ample::control::keysym::KEY_q))
    {
        if (isBig)
        {
            objectBig.setColor256(100, 100, 100);
            objectSmall.setColor256(200, 100, 100);
            current = &objectSmall;
            isBig = false;
        }
        else
        {
            objectBig.setColor256(200, 100, 100);
            objectSmall.setColor256(100, 100, 100);
            current = &objectBig;
            isBig = true;
        }
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_LEFT))
    {
        current->translate(-5, 0, 0);
    }
    else if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_RIGHT))
    {
        current->translate(5, 0, 0);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        current->translate(0, 0, 0.01);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        current->translate(0, 0, -0.01);
    }
    if (eventManager->mouse()->getWheelY() < 0)
    {
        current->scale(1.05, 1.05, 1.05);
    }
    else if (eventManager->mouse()->getWheelY() > 0)
    {
        current->scale(1 / 1.05, 1 / 1.05, 1 / 1.05);
    }
    if (eventManager->mouse()->isLeftDown())
    {
        current->rotate(1, 2, 3);
    }
}
