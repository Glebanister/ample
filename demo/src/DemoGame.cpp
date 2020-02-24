#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
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
    static ample::graphics::Vector2d<int> startPos{0, 0};
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        camera.translate(-5, 0, 0);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        camera.translate(5, 0, 0);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_w))
    {
        camera.translate(0, 0, 5);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_s))
    {
        camera.translate(0, 0, -5);
    }
    if (!eventManager->mouse()->isLeftDown())
    {
        camera.rotate(startPos.x - eventManager->mouse()->getMouseYRel() / getHeight() * 200,
                         startPos.y - eventManager->mouse()->getMouseXRel() / getWidth() * 200,
                         0);
    }
}
