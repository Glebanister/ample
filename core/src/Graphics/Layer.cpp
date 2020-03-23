#include <cassert>
#include <glm/glm.hpp>

#include "Debug.h"
#include "Layer.h"

namespace ample::graphics
{
void Layer::addCamera(Camera &camera)
{
    activity::Behaviour::addBehaviour(camera);
    _cameras.push_back(&camera);
}

void Layer::addObject(GraphicalObject &object)
{
    activity::Behaviour::addBehaviour(object);
    _objects.push_back(&object);
}

void Layer::onActive()
{
    DEBUG("Layer is active");
    activity::Behaviour::onActive();
    DEBUG("Layer iterating");
    for (auto cam : _cameras)
    {
        DEBUG("Camera look");
        cam->look();
        DEBUG("Camera is looking");
        for (auto obj : _objects)
        {
            DEBUG("Object draw");
            obj->draw();
            DEBUG("Object done");
        }
        DEBUG("Camera unlook");
        cam->unlook();
    }
    DEBUG("Layer is activated");
}

void Layer::clearCameras()
{
    _cameras.clear();
}

void Layer::clearObjecs()
{
    _objects.clear();
}
} // namespace ample::graphics
