#pragma once

#include "Activity.h"
#include "DemoGame.h"
#include "ScreenObject.h"

class SquareBehavior : public ample::activity::Activity
{
public:
    SquareBehavior(ample::window::WindowActivity &game, ample::graphics::ScreenObject &object);

    void onActive() override;

private:
    ample::window::WindowActivity &game;
    ample::graphics::ScreenObject &object;
};
