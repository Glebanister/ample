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
      object(ample::geometry::RegularPolygon<float>(10.0, 30),
             10.0f,
             50.0f,
             {1.0f, 1.0f},
             {1.0f, 1.0f},
             ample::graphics::normalsMode::FACE,
             {0.0f, 0.0f},
             0.0f)
{
    auto &level = createLevel(1, 10.0f, 0.5f);
    level.frontSlice().addObject(object);
    setCurrentLevel(1);
    level.camera().translate({0.0, 10.0, 0.0});
    cameraRemote = std::make_shared<KeyboardControlCamera>(eventManager(), level.camera());
    addBehaviour(*cameraRemote);
    level.frontSlice().addObject(cameraRemote->getLamp());
    texture = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw("../../demo/textures/braid.jpg",
                                                                                     {820UL / 7 - 1, 546UL / 4 - 1},
                                                                                     {2L, 2L},
                                                                                     {7, 4},
                                                                                     ample::graphics::channelMode::RGBA,
                                                                                     ample::graphics::texturePlayback::NORMAL,
                                                                                     27,
                                                                                     {
                                                                                         ample::graphics::textureOrigin::REVERSED,
                                                                                         ample::graphics::textureOrigin::REVERSED,
                                                                                     }));
    object.side().bindTexture(texture);
    object.face().bindTexture(texture);

    machine = std::make_shared<ample::game::StateMachine>();
    auto idle = std::make_shared<Idle>(object.face(), machine);
    auto running = std::make_shared<Running>(object.face(), machine);
    idle->addTransition(std::make_shared<ample::game::MouseTransition>(running,
                                                                       eventManager(),
                                                                       ample::game::MouseTransition::type::PRESSED,
                                                                       ample::control::mouseButton::BUTTON_LEFT,
                                                                       ample::geometry::Rectangle{
                                                                           {{0.0f, 0.0f},
                                                                            {static_cast<float>(getWidth()), static_cast<float>(getHeight())}},
                                                                       }));
    running->addTransition(std::make_shared<ample::game::KeyboardTransition>(idle,
                                                                             eventManager(),
                                                                             ample::game::KeyboardTransition::type::PRESSED,
                                                                             ample::control::keysym::SPACE));
    running->addTransition(std::make_shared<ample::game::TimerTransition>(idle, 3000));
    machine->setStartState(idle);

    addBehaviour(*machine);
}
