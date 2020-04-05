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
    : ample::game::game2d::Game2d(window),
      braid(std::make_shared<Braid>())
{
    auto &level = createLevel(1, 10.0f, 0.5f);
    level.frontSlice().addObject(*braid);
    setCurrentLevel(1);
    level.camera().translate({0.0, 10.0, 0.0});
    cameraRemote = std::make_shared<KeyboardControlCamera>(eventManager(), level.camera());
    addBehaviour(*cameraRemote);
    level.frontSlice().addObject(cameraRemote->getLamp());
    auto idle = std::make_shared<BraidIdle>("idle", braid);
    auto run = std::make_shared<BraidRun>("run", braid);
    idle->addTransition(std::make_shared<ample::game::MouseTransition>(run,
                                                                       eventManager(),
                                                                       ample::game::MouseTransition::type::PRESSED,
                                                                       ample::control::mouseButton::BUTTON_LEFT,
                                                                       ample::geometry::Rectangle{
                                                                           {{0.0f, 0.0f},
                                                                            {static_cast<float>(getWidth()), static_cast<float>(getHeight())}},
                                                                       }));
    run->addTransition(std::make_shared<ample::game::KeyboardTransition>(idle,
                                                                         eventManager(),
                                                                         ample::game::KeyboardTransition::type::PRESSED,
                                                                         ample::control::keysym::SPACE));
    run->addTransition(std::make_shared<ample::game::TimerTransition>(idle, 3000));
    braid->stateMachine()->setStartState(idle);
}
