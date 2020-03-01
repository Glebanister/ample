#include "LayeredWindowActivity.h"

namespace ample::graphics
{
LayeredWindowActivity::LayeredWindowActivity(window::Window &window)
    : WindowActivity(window) {}

void LayeredWindowActivity::addLayer(Layer &layer)
{
    DEBUG("Adding layer");
    Activity::addActivity(layer);
    _layers.push_back(&layer);
    DEBUG("Layer added");
}

void LayeredWindowActivity::cleanLayers()
{
    _layers.clear();
}
} // namespace ample::graphics
