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
    for (int i = 0; i < 1; i++)
    {
        objs.push_back(
            {
                {
                    {-300, -300},
                    {300, -300},
                    {300, 300},
                    {-300, 300},
                },

                {0, 0, i * 109.0},
            });
    }
    camera.translateSet(0, 0, objs.front().getZ());
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
    objs.back().rotate(0, -1, 1);

    _window.moveCursor(0, 0);
}
