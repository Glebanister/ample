#pragma once

#include <memory>

#include "Game2d.h"
#include "KeyboardControlCamera.h"
#include "Texture.h"
#include "StateMachine.h"

class AnimationSwapper : public ample::activity::Behavior
{
public:
    AnimationSwapper(ample::graphics::Texture *texture, size_t delta)
        : delta(delta), texture(texture)
    {
    }

    void onActive() override
    {
        ample::activity::Behavior::onActive();
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

class GraphicalObjectState : public ample::game::StateMachine::State
{
public:
    GraphicalObjectState(ample::graphics::GraphicalObject &object, std::shared_ptr<ample::game::StateMachine> machine)
        : State(machine), _object(object) {}

    ample::graphics::GraphicalObject &object()
    {
        return _object;
    }

private:
    ample::graphics::GraphicalObject &_object;
};

class Idle : public GraphicalObjectState
{
public:
    Idle(ample::graphics::GraphicalObject &object, std::shared_ptr<ample::game::StateMachine> machine)
        : GraphicalObjectState(object, machine) {}

    void onActive() override
    {
        GraphicalObjectState::onActive();
    }
};

class Running : public GraphicalObjectState
{
public:
    Running(ample::graphics::GraphicalObject &object, std::shared_ptr<ample::game::StateMachine> machine)
        : GraphicalObjectState(object, machine) {}

    void onActive() override
    {
        GraphicalObjectState::onActive();
        object().texture()->nextFrame();
    }
};

class DemoGame : public ample::game::game2d::Game2d
{
public:
    DemoGame(ample::window::Window &window);

private:
    ample::graphics::GraphicalObject2d object;
    std::shared_ptr<KeyboardControlCamera> cameraRemote;
    std::shared_ptr<ample::graphics::Texture> texture;
    std::shared_ptr<ample::game::StateMachine> machine;
};
