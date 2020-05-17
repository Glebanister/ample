#pragma once

#include <SDL2/SDL.h>
#include <ample/Window.h>
#include <ample/WindowActivity.h>
#include <imgui.h>
#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/LayeredWindowActivity.h"
#include "ample/Window.h"

namespace ample::gui
{
class ImguiActivity : public graphics::LayeredWindowActivity
{
public:
    ImguiActivity(const std::string &name,
                  const window::pixel_t &x,
                  const window::pixel_t &y,
                  const window::pixel_t &width,
                  const window::pixel_t &height,
                  const uint32_t &posFlags,
                  const uint32_t &modeFlags);

    void onActive() final;
    virtual void drawInterface();

    ~ImguiActivity();

protected:
};
} // namespace ample::gui
