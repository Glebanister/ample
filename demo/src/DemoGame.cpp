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
    auto obj1 = ample::graphics::GraphicalObject2d("ObjectName", "GraphicalObject", ample::geometry::RegularPolygon<float>(10.0f, 4), 10.0f, 3.0f, {1.0f, 2.0f}, {3.0f, 4.0f}, ample::graphics::normalsMode::FACE, {0.0f, 0.0f}, 1.0f);
    auto run = std::make_shared<ample::game::StateMachine::State>(obj1.stateMachine(), "run");
    // obj.idleState()->addTransition(std::make_shared<ample::game::MouseTransition>(run,
    //                                                                               eventManager(),
    //                                                                               ample::game::MouseTransition::type::PRESSED,
    //                                                                               ample::control::mouseButton::BUTTON_LEFT,
    //                                                                               ample::geometry::Rectangle{
    //                                                                                   {{0.0f, 0.0f},
    //                                                                                    {static_cast<float>(getWidth()), static_cast<float>(getHeight())}},
    //                                                                               }));
    // run->addTransition(std::make_shared<ample::game::KeyboardTransition>(obj.idleState(),
    //                                                                      eventManager(),
    //                                                                      ample::game::KeyboardTransition::type::PRESSED,
    //                                                                      ample::control::keysym::SPACE));
    obj1.idleState()->addTransition(std::make_shared<ample::game::TimerTransition>("transition_name", run, 3000));
    auto obj2 = ample::graphics::GraphicalObject2d("ObjectName", "GraphicalObject", ample::geometry::RegularPolygon<float>(10.0f, 4), 10.0f, 3.0f, {1.0f, 2.0f}, {3.0f, 4.0f}, ample::graphics::normalsMode::FACE, {0.0f, 0.0f}, 1.0f);
    ample::filing::Scene2d s{"front scene", {0.0f, 0.0f}, 1.0f, 43.0f, 0.3f};
    s.addObject(std::static_pointer_cast<ample::graphics::GraphicalObject>(obj1.facePointer()));
    s.addObject(std::static_pointer_cast<ample::graphics::GraphicalObject>(obj2.sidePointer()));
    std::cout << s.dump() << std::endl;

}

DemoGame::~DemoGame()
{
    // std::cout << Game2d::controller().dump() << std::endl;;
}
