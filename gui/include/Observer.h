#pragma once

#include "ample/Behaviour.h"
#include "ample/EventManager.h"
#include "ample/LightSource.h"
#include "ample/CameraPerspective.h"

namespace ample::gui
{

class Observer : public ample::activity::Behavior
{
public:
    Observer(ample::control::EventManager &manager, const graphics::Vector2d<int> &size = {1920, 1080});

    void onActive() override;

    ample::graphics::light::LightSource &getLamp();
    ample::graphics::CameraPerspective &getCamera();
    void onWindowResized(const graphics::Vector2d<int> &size);

protected:
    ample::control::EventManager &_manager;
    ample::graphics::light::LightSource _lamp;
    ample::graphics::CameraPerspective _camera;
    const float _cfX = 1.0f;
    const float _cfY = 1.0f;
};

} // namespace ample::gui
