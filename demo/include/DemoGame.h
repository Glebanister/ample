#pragma once

#include <memory>

#include "CameraOrtho.h"
#include "CameraPerspective.h"
#include "GraphicalObject2d.h"
#include "LayeredWindowActivity.h"
#include "LightSource.h"
#include "RegularPolygon.h"
#include "KeyboardControlCamera.h"

class DemoGame : public ample::graphics::LayeredWindowActivity
{
public:
    DemoGame(ample::window::Window &window);

private:
    KeyboardControlCamera<ample::graphics::CameraPerspective> camera{*eventManager};
    ample::graphics::CameraOrtho cameraOrtho{
        {1920, 1080},
        {0, 0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        -1920 / 10,
        1920 / 10,
        -1080 / 10,
        1080 / 10,
        0, 1000
    };
    ample::graphics::Layer layer;
    ample::graphics::GraphicalObject2d object{ample::geometry::RegularPolygon<float>(10, 7), 10, 0};
    ample::graphics::light::LightSource lamp;
};
