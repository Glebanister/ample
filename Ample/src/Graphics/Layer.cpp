#include "Layer.h"

namespace ample::graphics
{
void Layer::onActive()
{
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

void Layer::addCamera(std::shared_ptr<Camera> camera)
{
    _cameras.push_back(camera);
}

void Layer::clearCameras()
{
    _cameras.clear();
}

void Layer::addObject(std::shared_ptr<GraphicalObject> object)
{
    _objects.push_back(object);
}

void Layer::addObject(const std::vector<std::shared_ptr<GraphicalObject>> &objects)
{
    _objects.insert(_objects.end(), objects.begin(), objects.end());
}

void Layer::clearObjecs()
{
    _objects.clear();
}
} // namespace ample::graphics
