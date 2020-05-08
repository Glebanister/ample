#pragma once

#include <memory>
#include <vector>

#include "Debug.h"
#include "Layer.h"
#include "Window.h"
#include "WindowActivity.h"

namespace ample::graphics
{
class LayeredWindowActivity : public window::WindowActivity
{
public:
    LayeredWindowActivity(const std::string &name,
                          const pixel_t &x,
                          const pixel_t &y,
                          const pixel_t &width,
                          const pixel_t &height,
                          const uint32_t &posFlags,
                          const uint32_t &modeFlags);

    void addLayer(std::shared_ptr<Layer> layer);
    void cleanLayers();
    void onActive() override;
    void onAwake() override;

private:
    std::vector<std::shared_ptr<Layer>> _layers;
};
} // namespace ample::graphics
