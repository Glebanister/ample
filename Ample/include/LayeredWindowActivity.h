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

    void addLayer(const Layer &);
    void cleanLayers();

private:
    std::vector<std::shared_ptr<Layer>> _layers;
};
} // namespace ample::graphics
