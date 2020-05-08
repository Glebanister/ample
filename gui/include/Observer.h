#pragma once

#include "ample/Behaviour.h"
#include "ample/CameraPerspective.h"
#include "ample/EventManager.h"
#include "ample/Game2dEditor.h"
#include "ample/LightSource.h"
#include "ample/Singleton.h"

namespace ample::gui
{
class Observer
{
public:
    Observer(const graphics::Vector2d<float> &size = {1920, 1080});

    void look(std::shared_ptr<game::game2d::Level>) noexcept;

    void updatePos();

    void setViewport(const graphics::Vector2d<float> &size,
                     const graphics::Vector2d<float> &position);

protected:
    float _cfX = 1.0f;
    float _cfY = 1.0f;
    std::shared_ptr<ample::graphics::light::LightSource> _lamp;
    std::shared_ptr<ample::graphics::CameraPerspective> _camera;
};

} // namespace ample::gui
