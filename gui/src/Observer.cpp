#include "Observer.h"
#include "ample/Debug.h"
#include "ample/GraphicalPolygon.h"
#include "ample/RegularPolygon.h"
#include "ample/Utils.h"
#include "ample/Vector2d.h"

namespace ample::gui
{
Observer::Observer(const graphics::Vector2d<float> &size)
    : _lamp(std::make_shared<graphics::light::LightSource>("observer_lamp")),
      _camera(std::make_shared<graphics::CameraPerspective>("observer_camera",
                                                            graphics::Vector2d<graphics::pixel_t>{static_cast<int>(size.x),
                                                                                                  static_cast<int>(size.y)},
                                                            graphics::Vector2d<graphics::pixel_t>{0, 0},
                                                            graphics::Vector3d<float>{0.0, 0.0, 0.0},
                                                            graphics::Vector3d<float>{0.0, 0.0, 1.0},
                                                            60.0,
                                                            (static_cast<float>(size.x)) / (static_cast<float>(size.y)) * (_cfY / _cfX),
                                                            1.0,
                                                            1000.0))
{
    setViewport(size, {0.0f, 0.0f});
}

void Observer::setViewport(const graphics::Vector2d<float> &size,
                           const graphics::Vector2d<float> &position)
{
    _camera->setViewport({static_cast<int>(size.x), static_cast<int>(size.y)},
                         {static_cast<int>(position.x), static_cast<int>(position.y)});
    _camera->setAspectRatio(size.x / size.y);
}

void Observer::updatePos()
{
    _targetDistance += control::EventManager::instance().mouse().getWheelY() * 2.0f;
    if (control::EventManager::instance().keyboard().isKeyDown(control::keysym::ARROW_LEFT))
    {
        _camera->translate({1.0f, 0.0f, 0.0f});
    }
    if (control::EventManager::instance().keyboard().isKeyDown(control::keysym::ARROW_RIGHT))
    {
        _camera->translate({-1.0f, 0.0f, 0.0f});
    }
    if (control::EventManager::instance().keyboard().isKeyDown(control::keysym::ARROW_UP))
    {
        _camera->translate({0.0f, 1.0f, 0.0f});
    }
    if (control::EventManager::instance().keyboard().isKeyDown(control::keysym::ARROW_DOWN))
    {
        _camera->translate({0.0f, -1.0f, 0.0f});
    }
    _camera->translate({0.0f, 0.0f, (_targetDistance - _camera->getZ()) / 3.0f});

    _lamp->setTranslate({_camera->getX(), _camera->getY(), _camera->getZ()});
}

void Observer::look(std::shared_ptr<game::game2d::Level> level) noexcept
{
    ASSERT(level);
    _camera->look();
    _lamp->draw();
    auto obj1 = ample::graphics::GraphicalPolygon("ObjectName",
                                                  ample::geometry::RegularPolygon<float>(10.0f, 4),
                                                  10.0f,
                                                  {1.0f, 2.0f});
    obj1.draw();
    for (const auto &[_, slice] : level->layers())
    {
        utils::ignore(_);
        for (const auto &obj : slice->objects())
        {
            obj->draw();
        }
    }
    _camera->unlook();
}

void Observer::look(std::shared_ptr<filing::Scene2d> slice) noexcept
{
    ASSERT(slice);
    _camera->look();
    _lamp->draw();
    auto obj1 = ample::graphics::GraphicalPolygon("ObjectName",
                                                  ample::geometry::RegularPolygon<float>(10.0f, 4),
                                                  10.0f,
                                                  {1.0f, 2.0f});
    obj1.draw();
    for (const auto &obj : slice->objects())
    {
        obj->draw();
    }
    _camera->unlook();
}

void Observer::look(std::shared_ptr<graphics::GraphicalObject> object) noexcept
{
    ASSERT(object);
    _camera->look();
    _lamp->draw();
    object->draw();
    _camera->unlook();
}

void Observer::look(std::shared_ptr<physics::WorldObject2d> object) noexcept
{
    ASSERT(object);
    _camera->look();
    _lamp->draw();
    object->draw();
    _camera->unlook();
}

void Observer::look(std::shared_ptr<graphics::Texture>) noexcept
{
}
} // namespace ample::gui
