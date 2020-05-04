#pragma once

#include <memory>

#include "Game2dEditor.h"

class DemoGame : public ample::game::game2d::Game2dEditor
{
public:
    DemoGame(ample::window::Window &window);
};
