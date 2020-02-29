#include "LayeredWindowActivity.h"

namespace ample::graphics
{
LayeredWindowActivity::LayeredWindowActivity(window::Window &window)
    : WindowActivity(window) {}

void LayeredWindowActivity::addLayer(std::shared_ptr<Layer> layer)
{
    _layers.push_back(layer);
    addActivity(layer);
}

void LayeredWindowActivity::addLayer(const std::vector<std::shared_ptr<Layer>> &layers)
{
    for (auto layer : layers)
    {
        addLayer(layer);
    }
}

void LayeredWindowActivity::cleanLayers()
{
    _layers.clear();
}
} // namespace ample::graphics
