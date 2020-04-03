#include <SDL2/SDL.h>
#include <ample/WindowActivity.h>
#include <ample/Window.h>
#include <imgui_sdl.h>
#include <imgui.h>

#include "ImguiActivity.h"
#include "ample/Debug.h"
#include "ample/Exception.h"

namespace ample::gui
{
ImguiActivity::Renderer::Renderer(window::Window &window)
    : _renderer(SDL_CreateRenderer(window.pointer(), -1, SDL_RENDERER_ACCELERATED)) {}

SDL_Renderer *ImguiActivity::Renderer::pointer() const noexcept
{
    return _renderer;
}

ImguiActivity::Renderer::~Renderer()
{
    SDL_DestroyRenderer(_renderer);
}

ImguiActivity::ImguiActivity(ample::window::Window &window)
    : WindowActivity(window),
      _renderer(window)
{
    ImGui::CreateContext();
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    ImGuiSDL::Initialize(_renderer.pointer(), displayMode.w, displayMode.h);
}

void ImguiActivity::onResize()
{
    ample::window::WindowActivity::onResize();
}

void ImguiActivity::updateEnvironment() noexcept
{
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2(static_cast<float>(eventManager().mouse().getMouseX()), static_cast<float>(eventManager().mouse().getMouseY()));
    io.MouseDown[0] = eventManager().mouse().isLeftDown();
    io.MouseDown[1] = eventManager().mouse().isRightDown();
    io.MouseDown[2] = eventManager().mouse().isMiddleDown();
    io.MouseWheel = static_cast<float>(eventManager().mouse().getWheelY());
    io.MouseWheelH = static_cast<float>(eventManager().mouse().getWheelX());
    for (int i = 0; i < 512; ++i)
    {
        io.KeysDown[i] = eventManager().keyboard().isKeyDown(static_cast<ample::control::keysym>(i)) ? true : false;
    }
    for (char c = 0; c < CHAR_MAX; ++c)
    {
        if (eventManager().keyboard().isKeyPressed(static_cast<ample::control::keysym>(c)))
        {
            io.AddInputCharacterUTF16(c);
        }
    }
}

void ImguiActivity::presentGUI()
{
    ImGui::ShowDemoWindow();
}

void ImguiActivity::onActive()
{
    ample::window::WindowActivity::onActive();
    updateEnvironment();
    ImGui::NewFrame();
    presentGUI();
    SDL_SetRenderDrawColor(_renderer.pointer(), 114, 144, 154, 255);
    SDL_RenderClear(_renderer.pointer());
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());
    SDL_RenderPresent(_renderer.pointer());
}

ImguiActivity::~ImguiActivity()
{
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();
}
} // namespace ample::gui
