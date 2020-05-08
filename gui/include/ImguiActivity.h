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
    ImguiActivity(ample::window::Window &window);

    void onActive() final;
    virtual void drawInterface();

    ~ImguiActivity();

protected:
};
} // namespace ample::gui
