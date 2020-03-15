#pragma once

#include <SDL2/SDL.h>
#include <ample/WindowActivity.h>
#include <ample/Window.h>
#include <imgui_sdl.h>
#include <imgui.h>

namespace ample::gui
{
class ImguiActivity : public ample::window::WindowActivity
{
public:
    ImguiActivity(ample::window::Window &window);

    void onActive() override;

    ~ImguiActivity();

private:
    SDL_Renderer *_renderer;
    SDL_Texture *texture;
};
} // namespace ample::gui
