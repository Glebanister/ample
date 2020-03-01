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

void Layer::clearCameras()
{
    _cameras.clear();
}

void Layer::clearObjecs()
{
    _objects.clear();
}
} // namespace ample::graphics
