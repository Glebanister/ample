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

    void addLayer(std::shared_ptr<Layer> layer);
    void cleanLayers();
    void onActive() override;
    void onAwake() override;

private:
    std::vector<std::shared_ptr<Layer>> _layers;
};
} // namespace ample::graphics
