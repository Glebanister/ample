#include <cassert>

#include "Debug.h"
#include "Layer.h"

namespace ample::graphics
{
void Layer::addCamera(Camera &camera)
{
    _cameras.push_back(&camera);
}

void Layer::addObject(GraphicalObject &object)
{
    activity::Behaviour::addBehaviour(object);
    _objects.push_back(&object);
}

void Layer::onActive()
{
    activity::Behaviour::onActive();
    for (auto cam : _cameras)
    {
        cam->look();
        for (auto obj : _objects)
        {
            obj->draw();
        }
        cam->unlook();
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
} // namespace ample::graphics
