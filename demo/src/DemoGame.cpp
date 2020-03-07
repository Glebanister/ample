#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"
#include "WorldObject2d.h"
#include <memory>

#include "CameraBehavior.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    addActivity(*(new CameraBehavior{*this, camera}));
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    camera.look();
    object.draw();
    // camera.unlook();
}
