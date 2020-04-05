#pragma once

#include "EventManager.h"
#include "Camera.h"
#include "LightSource.h"
#include "Behaviour.h"

class KeyboardControlCamera : public ample::activity::Behavior
{
public:
    KeyboardControlCamera(ample::control::EventManager &manager, std::shared_ptr<ample::graphics::Camera> camera)
        : _manager(manager),
          _lamp(std::make_shared<ample::graphics::light::LightSource>()),
          _camera(camera)
    {
    }

    void onActive() override
    {
        if (_manager.keyboard().isKeyDown(ample::control::keysym::KEY_d))
        {
            _camera->moveRight(1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::KEY_a))
        {
            _camera->moveRight(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::ARROW_UP))
        {
            _camera->rotateUp(1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::ARROW_DOWN))
        {
            _camera->rotateUp(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::KEY_w))
        {
            _camera->moveForward(1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::KEY_s))
        {
            _camera->moveForward(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::ARROW_LEFT))
        {
            _camera->rotateRight(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::ARROW_RIGHT))
        {
            _camera->rotateRight(1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::COMMA))
        {
            _camera->rotateForward(-1);
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::PERIOD))
        {
            _camera->rotateForward(1);
        }
        _camera->rotateRight(-_manager.mouse().getMouseXRel() / (1.0 / 0.1));
        _camera->rotateUp(-_manager.mouse().getMouseYRel() / (1.0 / 0.1));
        _lamp->setTranslate({_camera->getX(), _camera->getY(), _camera->getZ()});

        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_1))
        {
            _lamp->addIntensitiy({-10, 0, 0});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_2))
        {
            _lamp->addIntensitiy({10, 0, 0});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_3))
        {
            _lamp->addIntensitiy({0, -10, 0});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_4))
        {
            _lamp->addIntensitiy({0, 10, 0});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_5))
        {
            _lamp->addIntensitiy({0, 0, -10});
        }
        if (_manager.keyboard().isKeyDown(ample::control::keysym::NUM_6))
        {
            _lamp->addIntensitiy({0, 0, 10});
        }
    }

    std::shared_ptr<ample::graphics::light::LightSource> getLamp()
    {
        return _lamp;
    }

protected:
    ample::control::EventManager &_manager;
    std::shared_ptr<ample::graphics::light::LightSource> _lamp;
    std::shared_ptr<ample::graphics::Camera> _camera;
};
