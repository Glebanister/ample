#pragma once

#include <memory>

#include "Game2d.h"

class DemoGame : public ample::game::game2d::Game2d
{
public:
    DemoGame(ample::window::Window &window);

private:
    std::unique_ptr<ample::graphics::GraphicalObject2d> object1;
    std::unique_ptr<ample::graphics::GraphicalObject2d> object2;
};
