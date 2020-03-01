#include <cassert>

#include "Layer.h"

namespace ample::graphics
{
void Layer::onActive()
{
    std::cerr << "Layer is active" << std::endl;
    activity::Activity::onActive();
    std::cerr << "Layer is active done" << std::endl;
    for (auto cam : _cameras)
    {
        std::cerr << "Camera look" << std::endl;
        cam->look();
        std::cerr << "Camera look done" << std::endl;
        std::cerr << "Iterating objecs" << std::endl;
        for (auto obj : _objects)
        {
            assert(obj.get());
            obj->draw();
        }
        std::cerr << "Iterating objecs done" << std::endl;
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
