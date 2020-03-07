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

    void onActive() override;
    bool isAng = false;
    ample::graphics::CameraOrtho camera{{1920, 1080}};
    CameraBehavior cameraBeh{*this, camera};
    ample::physics::WorldLayer2d worldLayer{{0.0f, -100.0f}};
    std::shared_ptr<ample::physics::WorldObject2d> ground;
    std::shared_ptr<ample::physics::WorldObject2d> brick;
    std::shared_ptr<ample::graphics::GraphicalObject2d> intoBrick;
    MyContactListener listener;
};
