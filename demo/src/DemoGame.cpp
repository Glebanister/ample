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
      object(ample::geometry::RegularPolygon<float>(10.0, 40, M_PI_4),
             10.0f,
             50.0f,
             {2.0f, 2.0f},
             {1.0f, 10.0f},
             ample::graphics::normalsMode::VERTEX,
             {0.0f, 0.0f},
             0.0f)
{
    _window.disableCursor();
    auto &level = createLevel(1, 10.0f, 0.5f);
    level.frontSlice().addObject(object);
    setCurrentLevel(1);
    level.camera().translate({0.0, 10.0, 0.0});
    cameraRemote = std::make_unique<KeyboardControlCamera>(*eventManager, level.camera());
    addBehaviour(*cameraRemote);
    level.frontSlice().addObject(cameraRemote->getLamp());
    texture = new ample::graphics::Texture(ample::graphics::TextureRaw("../../demo/textures/braid.jpg",
                                                                       {116UL, 135UL},
                                                                       {0L, 0L},
                                                                       {7, 4},
                                                                       ample::graphics::channelMode::RGB,
                                                                       ample::graphics::texturePlayback::NORMAL,
                                                                       27));
    object.face().bindTexture(std::shared_ptr<ample::graphics::Texture>(texture));
    swapper = new AnimationSwapper{texture, 20};
    textureSide = new ample::graphics::Texture(ample::graphics::TextureRaw("../../demo/textures/braid.jpg",
                                                                           {116UL, 135UL},
                                                                           {0L, 0L},
                                                                           {7, 4},
                                                                           ample::graphics::channelMode::RGB,
                                                                           ample::graphics::texturePlayback::NORMAL,
                                                                           27));
    object.side().bindTexture(std::shared_ptr<ample::graphics::Texture>(textureSide));
    swapperSide = new AnimationSwapper{textureSide, 20};
    addBehaviour(*swapperSide);
}

void DemoGame::onActive()
{
    Game2d::onActive();
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::SPACE))
    {
        texture->nextFrame();
    }
}
