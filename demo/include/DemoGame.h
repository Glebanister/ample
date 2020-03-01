#pragma once

#include <memory>

#include "WindowActivity.h"
#include "CameraOrtho.h"
#include "CameraPerspective.h"
#include "GraphicalObject2d.h"
#include "ScreenObject.h"
#include "PerlinNoise.h"
#include "WorldLayer2d.h"
#include "Vector2d.h"
#include "CameraBehavior.h"
#include "LayeredWindowActivity.h"
#include "SquareBehavior.h"

class DemoGame : public ample::graphics::LayeredWindowActivity
{
public:
    DemoGame(ample::window::Window &window);

private:
    void onAwake() override;
    void onActive() override;

    ample::graphics::CameraOrtho camera{{1920, 1080}};
    CameraBehavior cameraBeh{*this, camera};
    ample::physics::WorldLayer2d worldLayer{{0.0f, 0.0f}};
    std::shared_ptr<ample::physics::WorldObject2d> ground;
    std::shared_ptr<ample::physics::WorldObject2d> brick;
};
