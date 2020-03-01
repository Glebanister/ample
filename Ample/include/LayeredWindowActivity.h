#pragma once

#include <vector>
#include <memory>

#include "WindowActivity.h"
#include "Layer.h"
#include "Window.h"

namespace ample::graphics
{
class LayeredWindowActivity : public window::WindowActivity
{
public:
    LayeredWindowActivity(window::Window &window);

    template <class TLayer>
    void addLayer(const TLayer &layer)
    {
        Activity::addActivity(layer);
        _layers.push_back(std::make_shared<TLayer>(layer));
    }
    void cleanLayers();

private:
    std::vector<std::shared_ptr<Layer>> _layers;
};
} // namespace ample::graphics
