#pragma once

#include <memory>

#include "Game2d.h"
#include "KeyboardControlCamera.h"
#include "Texture.h"
#include "StateMachine.h"
#include "ControlledObject.h"
#include "Debug.h"
#include "RegularPolygon.h"

class Braid : public ample::graphics::GraphicalObject2d
{
public:
    Braid()
        : GraphicalObject2d(ample::geometry::RegularPolygon<float>(10.0f, 6),
                            10.0f,
                            0.0f,
                            {1.0f, 1.0f},
                            {1.0f, 1.0f},
                            ample::graphics::normalsMode::FACE,
                            "Braid",
                            {0.0f, 0.0f},
                            0.0f)
    {
        auto texture = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw("../../demo/textures/braid.jpg",
                                                                                              "Braid textre",
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
        bindTexture(texture);
        face().bindTexture(texture);
        side().bindTexture(texture);
    }
};

class BraidIdle : public ample::game::ControlledObject::ObjectState<Braid>
{
public:
    BraidIdle(const std::string &name, std::shared_ptr<Braid> braid)
        : ObjectState(name, braid) {}

    void onActive() override
    {
        ObjectState::onActive();
    }
};

class BraidRun : public ample::game::ControlledObject::ObjectState<Braid>
{
public:
    BraidRun(const std::string &name, std::shared_ptr<Braid> braid)
        : ObjectState(name, braid) {}

    void onActive() override
    {
        ObjectState::onActive();
        object()->texture()->nextFrame();
    }
};

class DemoGame : public ample::game::game2d::Game2d
{
public:
    DemoGame(ample::window::Window &window);

private:
    std::shared_ptr<Braid> braid;
    std::shared_ptr<KeyboardControlCamera> cameraRemote;
    std::shared_ptr<ample::graphics::Texture> texture;
};
