#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "DemoGame.h"
#include "RegularPolygon.h"
#include "Texture.h"
#include "Clock.h"
#include "KeyboardTransition.h"
#include "MouseTransition.h"
#include "TimerTransition.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::game::game2d::Game2d(window)
{
    auto level = createLevel(1, 10.0f, 0.5f);
    setCurrentLevel(1);
    level->camera()->translate({0.0, 10.0, 0.0});
    cameraRemote = std::make_shared<KeyboardControlCamera>(eventManager(), level->camera());
    addBehavior(std::static_pointer_cast<Behavior>(cameraRemote));
    level->frontSlice()->addObject(std::static_pointer_cast<ample::graphics::GraphicalObject>(cameraRemote->getLamp()));

    // level->frontSlice()->addObject(...); // add object
}
