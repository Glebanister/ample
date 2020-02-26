#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"
#include <memory>

DemoGame::DemoGame(ample::window::Window &window)
    : ample::window::WindowActivity(window)
{
    addActivity(cameraBeh);
    for (int i = 0; i < 10; i++)
    {
        objs.push_back(
            {
                {
                    {-300, -300},
                    {300, -300},
                    {300, 300},
                    {-300, 300},
                },

                {0, 0, i * 109},
            });
        objs.back().setColor256(rand() % 256, rand() % 256, rand() % 256);
    }
    camera.translateSet(0, 0, objs.back().getZ());
}

void DemoGame::onAwake()
{
    WindowActivity::onAwake();
    _window.disableCursor();
}

void DemoGame::onActive()
{
    WindowActivity::onActive();
    camera.look();
    for (auto obj : objs)
    {
        obj.draw();
    }
    camera.unlook();

    screenCamera.look();
    ample::graphics::ScreenObject({{-3, -3}, {3, -3}, {3, 3}, {-3, 3}}, {0, 0, 0}).draw();
    screenCamera.unlook();
    if (eventManager->mouse()->getWheelY() < 0)
    {
        camera.setPerspective(camera.getLeft(), camera.getRight(), camera.getBottom(), camera.getTop(), camera.getNear() + 10, camera.getFar());
    }
    else if (eventManager->mouse()->getWheelY() > 0)
    {
        camera.setPerspective(camera.getLeft(), camera.getRight(), camera.getBottom(), camera.getTop(), camera.getNear() - 10, camera.getFar());
    }

    _window.moveCursor(0, 0);
}
