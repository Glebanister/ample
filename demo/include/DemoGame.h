#pragma once

#include "WindowActivity.h"
#include "ScreenCamera.h"
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

    ample::graphics::ScreenCamera camera{{1960, 1080}, {1960, 1080}};
    ample::graphics::ScreenObject object{{{-20, -20},
                                          {20, -20},
                                          {20, 20},
                                          {-20, 20}}};
    ample::random::PerlinNoise xNoise{103};
    ample::random::PerlinNoise yNoise{23};
};
