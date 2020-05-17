#include <algorithm>
#include <cassert>
#include <glm/glm.hpp>

#include "Debug.h"
#include "Layer.h"

namespace ample::graphics
{
Layer::Layer(std::shared_ptr<game::Namespace> ns)
    : _levelNamespace(ns) {}

void Layer::addCamera(std::shared_ptr<Camera> camera)
{
    activity::Behavior::addBehavior(std::static_pointer_cast<Behavior>(camera));
    _cameras.push_back(camera);
    _levelNamespace->addObject(camera);
}

void Layer::addObject(std::shared_ptr<GraphicalObject> object)
{
    activity::Behavior::addBehavior(std::static_pointer_cast<Behavior>(object));
    _objects.push_back(object);
    _levelNamespace->addObject(object);
}

void Layer::removeObject(std::shared_ptr<GraphicalObject> object)
{
    activity::Behavior::removeBehavior(std::static_pointer_cast<Behavior>(object));
    _objects.erase(std::remove(_objects.begin(), _objects.end(), object), _objects.end());
    _levelNamespace->removeObject(object);
}

void Layer::setVisibility(bool value) noexcept
{
    _visible = value;
}

void Layer::onActive()
{
    activity::Behavior::onActive();
    if (_visible)
    {
        for (auto cam : _cameras)
        {
            if (cam->visible())
            {
                cam->look();
                for (auto obj : _objects)
                {
                    obj->draw();
                }
                cam->unlook();
            }
        }
    }
}

void Layer::clearCameras()
{
    _cameras.clear();
}

std::vector<std::shared_ptr<GraphicalObject>> &Layer::objects() noexcept
{
    return _objects;
}
std::vector<std::shared_ptr<Camera>> &Layer::cameras() noexcept
{
    return _cameras;
}

std::shared_ptr<game::Namespace> Layer::getNamespace() const noexcept
{
    return _levelNamespace;
}
} // namespace ample::graphics
