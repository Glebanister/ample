#include "ample/Debug.h"
#include "Observer.h"
#include "ample/Vector2d.h"

namespace ample::gui
{
Observer::Observer(ample::control::EventManager &manager, const graphics::Vector2d<int> &size)
    : _manager(manager),
      _lamp(std::make_shared<graphics::light::LightSource>("observer_lamp")),
      _camera(std::make_shared<graphics::CameraPerspective>(graphics::Vector2d<graphics::pixel_t>{size.x, size.y},
                                                            graphics::Vector2d<graphics::pixel_t>{0, 0},
                                                            graphics::Vector3d<float>{0.0, 0.0, 0.0},
                                                            graphics::Vector3d<float>{0.0, 0.0, 1.0},
                                                            60.0,
                                                            (static_cast<float>(size.x)) / (static_cast<float>(size.y)) * (_cfY / _cfX),
                                                            1.0,
                                                            1000.0))
{
    onWindowResized(size);
}

void Observer::onWindowResized(const graphics::Vector2d<int> &size)
{
    int viewportW = size.x * _cfX;
    int viewportH = size.y * _cfY;
    _camera->setViewport({viewportW, viewportH}, {(size.x - viewportW) / 2, (size.y - viewportH)});
    _camera->setAspectRatio((static_cast<float>(size.x)) / (static_cast<float>(size.y)) * (_cfX / _cfY));
}

void Observer::onActive()
{
    Behavior::onActive();
    if (_manager.keyboard().isKeyDown(control::keysym::ARROW_LEFT))
    {
        _camera->translate({1.0f, 0.0f, 0.0f});
    }
    if (_manager.keyboard().isKeyDown(control::keysym::ARROW_RIGHT))
    {
        _camera->translate({-1.0f, 0.0f, 0.0f});
    }
    if (_manager.keyboard().isKeyDown(control::keysym::ARROW_UP))
    {
        _camera->translate({0.0f, 1.0f, 0.0f});
    }
    if (_manager.keyboard().isKeyDown(control::keysym::ARROW_DOWN))
    {
        _camera->translate({0.0f, -1.0f, 0.0f});
    }
    _camera->translate({0.0f, 0.0f, 2.0f * _manager.mouse().getWheelY()});

    _lamp->setTranslate({_camera->getX(), _camera->getY(), _camera->getZ()});
}

std::shared_ptr<ample::graphics::light::LightSource> Observer::getLamp()
{
    return _lamp;
}

std::shared_ptr<ample::graphics::CameraPerspective> Observer::getCamera()
{
    return _camera;
}
} // namespace ample::gui
