#include "LayeredWindowActivity.h"

namespace ample::graphics
{
LayeredWindowActivity::LayeredWindowActivity(window::Window &window)
    : WindowActivity(window) {}

void LayeredWindowActivity::cleanLayers()
{
    _layers.clear();
}
} // namespace ample::graphics
