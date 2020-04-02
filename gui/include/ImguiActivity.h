#pragma once

#include <SDL2/SDL.h>
#include <ample/WindowActivity.h>
#include <ample/Window.h>
#include <imgui_sdl.h>
#include <imgui.h>

#include "ample/Window.h"

namespace ample::gui
{
class ImguiActivity : public ample::window::WindowActivity
{
public:
    ImguiActivity(ample::window::Window &window);

    void onActive() override;
    void onResize() override;

    void updateEnvironment() noexcept;
    virtual void presentGUI();

    ~ImguiActivity();

private:
    class Renderer
    {
    public:
        Renderer(window::Window &window);
        SDL_Renderer *pointer() const noexcept;
        ~Renderer();

    private:
        SDL_Renderer *_renderer;
    };

    Renderer _renderer;
};
} // namespace ample::gui
