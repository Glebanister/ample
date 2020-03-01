#include "Layer.h"

namespace ample::graphics
{
void Layer::onActive()
{
    activity::Activity::onActive();
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

void Layer::addCamera(const Camera &camera)
{
    _cameras.push_back(std::make_shared<Camera>(camera));
}

void Layer::clearCameras()
{
    _cameras.clear();
}

void Layer::addObject(const GraphicalObject &object)
{
    _objects.push_back(std::make_shared<GraphicalObject>(object));
}

void Layer::clearObjecs()
{
    _objects.clear();
}
} // namespace ample::graphics
