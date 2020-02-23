#pragma once

#include "WindowActivity.h"
#include "CameraOrtho.h"
#include "CameraPerspective.h"
#include "GraphicalObject2d.h"
#include "ScreenObject.h"
#include "PerlinNoise.h"

class DemoGame : public ample::window::WindowActivity
{
public:
    DemoGame(ample::window::Window &window);

private:
    void onAwake() override;
    void onActive() override;

    ample::graphics::CameraPerspective camera{{1960, 1080}};
    ample::graphics::ScreenObject objectSmall{{{-20, -20},
                                               {20, -20},
                                               {20, 20},
                                               {-20, 20}}};
    ample::graphics::ScreenObject objectBig{{{-30, -30},
                                             {30, -30},
                                             {30, 30},
                                             {-30, 30}}};
    ample::random::PerlinNoise xNoise{103};
    ample::random::PerlinNoise yNoise{23};
};
