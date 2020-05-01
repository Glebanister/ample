#include <cassert>
#include <glm/glm.hpp>
#include <algorithm>

#include "Debug.h"
#include "Layer.h"

namespace ample::graphics
{
void Layer::addCamera(std::shared_ptr<Camera> camera)
{
    activity::Behavior::addBehavior(std::static_pointer_cast<Behavior>(camera));
    _cameras.push_back(camera);
}

void Layer::addObject(std::shared_ptr<GraphicalObject> object)
{
    activity::Behavior::addBehavior(std::static_pointer_cast<Behavior>(object));
    _objects.push_back(object);
}

void Layer::removeObject(std::shared_ptr<GraphicalObject> object)
{
    activity::Behavior::removeBehavior(std::static_pointer_cast<Behavior>(object));
    _objects.erase(std::remove(_objects.begin(), _objects.end(), object), _objects.end());
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

size_t Layer::objectsCount() const noexcept
{
    return _objects.size();
}

std::vector<std::shared_ptr<GraphicalObject>> &Layer::objects() noexcept
{
    return _objects;
}
} // namespace ample::graphics
