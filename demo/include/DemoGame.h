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
#include "Scene2d.h"
#include "ContactListener.h"

class MyContactListener : public ample::physics::ContactListener {
    void startContact(ample::physics::Fixture& fixtureA, ample::physics::Fixture& fixtureB) override;
    void endContact(ample::physics::Fixture& fixtureA, ample::physics::Fixture& fixtureB) override;
};


class DemoGame : public ample::graphics::LayeredWindowActivity
{
public:
    DemoGame(ample::window::Window &window);

private:
    void leftArrow();
    void rightArrow();
    void upArrow();
    void downArrow();

    ample::graphics::CameraPerspective camera{
        {1920, 1080},
        {0, 0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        1.0,
        120.0,
        1920.0 / 1080.0,
        0.1,
        1000.0,
    };
    
    void onActive() override;

    std::vector<ample::graphics::Vector2d<float>> shape{{-200.0f, -200.0f}, {-200.0f, 200.0f}, {200.0f, 200.0f}, {200.0f, -200.0f}};
    ample::graphics::ScreenObject object{shape, {0.0f, 0.0f, 0.0f}, 50.0};
    // std::shared_ptr<ample::physics::WorldObject2d> brick;
};
