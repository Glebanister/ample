#pragma once

#include <vector>
#include <memory>

#include "WindowActivity.h"
#include "Layer.h"
#include "Window.h"
#include "Debug.h"

namespace ample::graphics
{
class LayeredWindowActivity : public window::WindowActivity
{
public:
    LayeredWindowActivity(window::Window &window);

    void addLayer(Layer &layer);
    void cleanLayers();
    void onActive() override;
    void onAwake() override;

private:
    std::vector<Layer *> _layers;
};
} // namespace ample::graphics
