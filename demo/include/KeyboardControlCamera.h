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
        this->translate({-1, 0, 0});
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        this->translate({1, 0, 0});
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        this->translate({0, 1, 0});
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        this->translate({0, -1, 0});
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::KEY_w))
    {
        this->translate({0, 0, 1});
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::KEY_s))
    {
        this->translate({0, 0, -1});
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::ARROW_LEFT))
    {
        this->rotate({0, 1, 0}, 1.0);
    }
    if (_manager.keyboard()->isKeyDown(ample::control::keysym::ARROW_RIGHT))
    {
        this->rotate({0, 1, 0}, -1.0);
    }
}
