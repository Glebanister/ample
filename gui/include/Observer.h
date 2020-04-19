#pragma once

#include "ample/Behaviour.h"
#include "ample/EventManager.h"
#include "ample/LightSource.h"
#include "ample/CameraPerspective.h"
#include "ample/Game2d.h"
#include "AmpleGui.h"

namespace ample::gui
{
class AmpleGui;
} // namespace ample::gui

namespace ample::gui
{
class Observer : public ample::activity::Behavior
{
public:
    Observer(gui::AmpleGui &gui, const graphics::Vector2d<int> &size = {1920, 1080});

    void onActive() override;

    std::shared_ptr<ample::graphics::light::LightSource> getLamp();
    std::shared_ptr<ample::graphics::CameraPerspective> getCamera();
    void onWindowResized(const graphics::Vector2d<int> &size);

protected:
    ample::control::EventManager &_manager;
    ample::game::game2d::Game2d &_game;
    std::shared_ptr<ample::graphics::light::LightSource> _lamp;
    std::shared_ptr<ample::graphics::CameraPerspective> _camera;
    const float _cfX = 1.0f;
    const float _cfY = 1.0f;
};

} // namespace ample::gui
