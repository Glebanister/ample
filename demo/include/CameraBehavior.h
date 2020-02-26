#pragma once

#include "Activity.h"
#include "WindowActivity.h"
#include "Camera.h"

class CameraBehavior : public ample::activity::Activity
{
public:
    CameraBehavior(ample::window::WindowActivity &game, ample::graphics::Camera &camera);

    void onActive() override;

private:
    ample::window::WindowActivity &game;
    ample::graphics::Camera &camera;
};
