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
#include "Factory.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::game::game2d::Game2d(window)
{
    firstLevel = Game2d::createLevel("first", 10.0f, 0.5f, {0.0f, -10.0f}, "first_level");
    setCurrentLevel(firstLevel);
    // auto obj = std::shared_ptr<ample::physics::WorldObject2d>(new ample::physics::WorldObject2d("ground",
    //                                                                                             firstLevel->frontSlice(),
    //                                                                                             ample::physics::BodyType::STATIC_BODY,
    //                                                                                             {{30, 10}, {30, -5}, {-30, -5}, {-30, 2}},
    //                                                                                             1.0,
    //                                                                                             {10.0f, 5.0f},
    //                                                                                             {1.0f, 10.0f},
    //                                                                                             ample::graphics::normalsMode::FACE,
    //                                                                                             {-50, -50}));
    firstLevel->save();
}
