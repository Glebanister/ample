#pragma once

#include <memory>

#include "CameraOrtho.h"
#include "CameraPerspective.h"
#include "GraphicalObject2d.h"
#include "ScreenObject.h"
#include "PerlinNoise.h"
#include "WorldLayer2d.h"
#include "Vector2d.h"
#include "LayeredWindowActivity.h"
#include "Scene2d.h"
#include "ContactListener.h"
#include "LightSource.h"
#include "RegularPolygon.h"
#include "KeyboardControlCamera.h"

class DemoGame : public ample::graphics::LayeredWindowActivity
{
public:
    DemoGame(ample::window::Window &window);

    void onActive() override;

private:
    KeyboardControlCamera<ample::graphics::CameraPerspective> camera {*eventManager};
    ample::graphics::CameraOrtho cameraOrtho {
            {1920, 1080},
            {0, 0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 1.0},
            -1920 / 10,
            1920 / 10,
            -1080 / 10,
            1080 / 10,
            0,
            1000};
    ample::graphics::Layer layer;
    std::unique_ptr<ample::graphics::GraphicalObject2d> object1;
    std::unique_ptr<ample::graphics::GraphicalObject2d> object2;
};
