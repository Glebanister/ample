#pragma once

#include <memory>

#include "Game2d.h"
#include "KeyboardControlCamera.h"
#include "Texture.h"

class AnimationSwapper : public ample::activity::Behaviour
{
public:
    AnimationSwapper(ample::graphics::Texture *texture, size_t delta)
        : delta(delta), texture(texture)
    {
    }

    void onActive() override
    {
        ample::activity::Behaviour::onActive();
        auto curTime = ample::time::Clock::globalTimeMs();
        if (curTime - lastTime > delta)
        {
            texture->nextFrame();
            lastTime = curTime;
        }
    }

private:
    ample::graphics::Texture *texture;
    size_t delta;
    int lastTime = 0;
};

class DemoGame : public ample::game::game2d::Game2d
{
public:
    DemoGame(ample::window::Window &window);

    void onActive() override;

private:
    ample::graphics::GraphicalObject2d object;
    std::unique_ptr<KeyboardControlCamera> cameraRemote;
    ample::graphics::Texture *texture;
    ample::graphics::Texture *textureSide;
    AnimationSwapper *swapper;
    AnimationSwapper *swapperSide;
};
