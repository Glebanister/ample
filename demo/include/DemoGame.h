#pragma once

#include <memory>

#include "WindowActivity.h"
#include "CameraOrtho.h"
#include "CameraPerspective.h"
#include "GraphicalObject2d.h"
#include "ScreenObject.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"

class DemoGame : public ample::window::WindowActivity
{
public:
    DemoGame(ample::window::Window &window);

private:
    void onAwake() override;
    void onActive() override;

    ample::graphics::CameraPerspective camera{{1920, 1080}};
    ample::graphics::ScreenObject objectSmall{{{-10, -10},
                                               {10, -10},
                                               {10, 10},
                                               {-10, 10}}};
    ample::graphics::ScreenObject objectBig{{{-300, -300},
                                             {300, -300},
                                             {300, 300},
                                             {-300, 300}}};
    ample::random::PerlinNoise xNoise{103};
    ample::random::PerlinNoise yNoise{23};
    ample::graphics::ScreenObject *current = &objectBig;
    ample::graphics::CameraOrtho screenCamera{{1920, 1080}};
    CameraBehavior cameraBeh{*this, camera};
};
