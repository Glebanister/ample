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

private:
    void onActive() override;
    KeyboardControlCamera<ample::graphics::CameraPerspective> camera{*eventManager};
    ample::graphics::Layer layer;
    ample::graphics::GraphicalObject2d object{ample::geometry::RegularPolygon<float>(10, 7), 10, 0};
    ample::graphics::light::LightSource lamp;
};
