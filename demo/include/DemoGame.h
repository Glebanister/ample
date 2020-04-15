#pragma once

#include <memory>

#include "Game2d.h"
#include "KeyboardControlCamera.h"
#include "Texture.h"
#include "StateMachine.h"
#include "ControlledObject.h"
#include "Debug.h"
#include "RegularPolygon.h"

class DemoGame : public ample::game::game2d::Game2d
{
public:
    DemoGame(ample::window::Window &window);
    ~DemoGame();
};
