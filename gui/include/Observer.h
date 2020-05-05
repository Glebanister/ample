#pragma once

#include "ample/Behaviour.h"
#include "ample/EventManager.h"
#include "ample/LightSource.h"
#include "ample/CameraPerspective.h"
#include "ample/Game2dEditor.h"

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
    Observer(const graphics::Vector2d<int> &size = {1920, 1080});

    void onActive() override;

    std::shared_ptr<ample::graphics::light::LightSource> getLamp();
    std::shared_ptr<ample::graphics::CameraPerspective> getCamera();
    void onWindowResized(const graphics::Vector2d<int> &size);

    void setLevel(std::shared_ptr<game::game2d::Level>) noexcept;
    void loseLevel() noexcept;

protected:
    float _cfX = 1.0f;
    float _cfY = 1.0f;
    std::shared_ptr<game::game2d::Level> _level = nullptr;
    std::shared_ptr<ample::graphics::light::LightSource> _lamp;
    std::shared_ptr<ample::graphics::CameraPerspective> _camera;
};

} // namespace ample::gui
