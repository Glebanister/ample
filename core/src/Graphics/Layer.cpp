#include <cassert>
#include <glm/glm.hpp>

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

void Layer::clearObjecs()
{
    _objects.clear();
}
size_t Layer::objectsCount() const noexcept
{
    return _objects.size();
}
} // namespace ample::graphics
