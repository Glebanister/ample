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
#include "LightSource.h"
#include "RegularPolygon.h"


#include "GraphicalObject2dIO.h"

class MyContactListener : public ample::physics::ContactListener
{
    void startContact(ample::physics::Fixture &fixtureA, ample::physics::Fixture &fixtureB) override;
    void endContact(ample::physics::Fixture &fixtureA, ample::physics::Fixture &fixtureB) override;
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

    void onActive() override;
    bool isAng = false;
    ample::graphics::CameraPerspective camera{
        {1920, 1080},
        {0, 0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        60.0,
        1920.0 / 1080.0,
        0.1,
        1000.0,
    };
    CameraBehavior cameraBeh{*this, camera};
    ample::physics::WorldLayer2d worldLayer{{0.0f, -100.0f}};
    ample::physics::WorldObject2d* ground;
    ample::physics::WorldObject2d* brick1;
    ample::physics::WorldObject2d* brick2;
    ample::physics::WorldObject2d* brick3;
    ample::physics::WorldObject2d* ground2;
    MyContactListener listener;
    ample::graphics::light::LightSource lamp;
    ample::random::PerlinNoise noise{42};
};
