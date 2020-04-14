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
    // auto level = createLevel(1, 10.0f, 0.5f);
    // setCurrentLevel(1);
    // level->camera()->translate({0.0, 10.0, 0.0});
    // cameraRemote = std::make_shared<KeyboardControlCamera>(eventManager(), level->camera());
    // addBehavior(std::static_pointer_cast<Behavior>(cameraRemote));
    // level->frontSlice()->addObject(std::static_pointer_cast<ample::graphics::GraphicalObject>(cameraRemote->getLamp()));

    // level->frontSlice()->addObject(...); // add object
    // Game2d::controller().stateMachine()->se
    std::cout << ample::graphics::GraphicalObject2d("ObjectName", "GraphicalObject", ample::geometry::RegularPolygon<float>(10.0f, 4), 10.0f, 3.0f, {1.0f, 2.0f}, {3.0f, 4.0f}, ample::graphics::normalsMode::FACE, {0.0f, 0.0f}, 1.0f).dump() << std::endl;
}

DemoGame::~DemoGame()
{
    // std::cout << Game2d::controller().dump() << std::endl;;
}
