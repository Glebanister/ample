#pragma once

#include "EventManager.h"
#include "CameraPerspective.h"

template <class CameraT>
class KeyboardControlCamera : public CameraT
{
public:
    KeyboardControlCamera(ample::control::EventManager &manager);
    void onActive() override;

protected:
    ample::control::EventManager &_manager;
};

template <class CameraT>
KeyboardControlCamera<CameraT>::KeyboardControlCamera(ample::control::EventManager &manager)
    : CameraT({1920, 1080},
              {0, 0},
              {0.0, 0.0, 0.0},
              {0.0, 0.0, 1.0},
              60.0,
              1920.0 / 1080.0,
              0.1,
              1000.0),
      _manager(manager)
{
}

template <class CameraT>
void KeyboardControlCamera<CameraT>::onActive()
{
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        this->moveRight(1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        this->moveRight(-1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        this->rotateUp(1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        this->rotateUp(-1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::KEY_w))
    {
        this->moveForward(1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::KEY_s))
    {
        this->moveForward(-1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::ARROW_LEFT))
    {
        this->rotateRight(-1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::ARROW_RIGHT))
    {
        this->rotateRight(1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::COMMA))
    {
        this->rotateForward(-1);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::PERIOD))
    {
        this->rotateForward(1);
    }
    this->rotateRight(-_manager.mouse()->getMouseXRel() / 5.0);
    this->rotateUp(-_manager.mouse()->getMouseYRel() / 5.0);
}
