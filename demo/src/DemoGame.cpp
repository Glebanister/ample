#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "DemoGame.h"
#include "RegularPolygon.h"
#include "Texture.h"
#include "Clock.h"

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
    osWindow().disableCursor();
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

    swapper = std::make_shared<AnimationSwapper>(texture.get(), 15);
    addBehaviour(*swapper);
}
