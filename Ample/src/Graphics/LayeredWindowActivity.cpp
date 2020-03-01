#include "LayeredWindowActivity.h"

namespace ample::graphics
{
LayeredWindowActivity::LayeredWindowActivity(window::Window &window)
    : WindowActivity(window) {}

void LayeredWindowActivity::addLayer(const Layer &layer)
{
    _layers.push_back(std::make_shared<Layer>(layer));
    addActivity(layer);
}

void LayeredWindowActivity::cleanLayers()
{
    _layers.clear();
}
} // namespace ample::graphics
