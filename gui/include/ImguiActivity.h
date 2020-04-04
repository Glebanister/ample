#pragma once

#include <SDL2/SDL.h>
#include <ample/WindowActivity.h>
#include <ample/Window.h>
#include <imgui.h>
#include <memory>

#include "ample/Window.h"
#include "ample/LayeredWindowActivity.h"
#include "ample/Game2d.h"

namespace ample::gui
{
class ImguiActivity : public ample::game::game2d::Game2d
{
public:
    ImguiActivity(ample::window::Window &window);

    void onActive() override;

    ~ImguiActivity();

protected:
    virtual void drawInterface();
};
} // namespace ample::gui
