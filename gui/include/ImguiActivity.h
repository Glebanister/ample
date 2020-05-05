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
class ImguiActivity : public game::game2d::Game2dEditor
{
public:
    ImguiActivity(ample::window::Window &window);
    ImguiActivity(ample::window::Window &window,
                  const std::filesystem::path &existingProjectPath);

    void onActive() override;

    ~ImguiActivity();

protected:
    virtual void drawInterface();
};
} // namespace ample::gui
