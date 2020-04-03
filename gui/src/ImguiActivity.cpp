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
    ImGuiIO &io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_Tab] = control::KeyboardManager::C_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = control::KeyboardManager::C_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = control::KeyboardManager::C_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = control::KeyboardManager::C_UP;
    io.KeyMap[ImGuiKey_DownArrow] = control::KeyboardManager::C_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = control::KeyboardManager::C_PAGEUP;
    io.KeyMap[ImGuiKey_PageDown] = control::KeyboardManager::C_PAGEDOWN;
    io.KeyMap[ImGuiKey_Home] = control::KeyboardManager::C_HOME;
    io.KeyMap[ImGuiKey_End] = control::KeyboardManager::C_END;
    io.KeyMap[ImGuiKey_Insert] = control::KeyboardManager::C_INSERT;
    io.KeyMap[ImGuiKey_Delete] = control::KeyboardManager::C_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = control::KeyboardManager::C_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = control::KeyboardManager::C_SPACE;
    io.KeyMap[ImGuiKey_Enter] = control::KeyboardManager::C_ENTER;
    io.KeyMap[ImGuiKey_Escape] = control::KeyboardManager::C_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = control::KeyboardManager::C_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = control::KeyboardManager::A;
    io.KeyMap[ImGuiKey_C] = control::KeyboardManager::C;
    io.KeyMap[ImGuiKey_V] = control::KeyboardManager::V;
    io.KeyMap[ImGuiKey_X] = control::KeyboardManager::X;
    io.KeyMap[ImGuiKey_Y] = control::KeyboardManager::Y;
    io.KeyMap[ImGuiKey_Z] = control::KeyboardManager::Z;
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
    io.MouseWheelH = static_cast<float>(eventManager().mouse().getWheelX());
    io.MouseWheel = static_cast<float>(eventManager().mouse().getWheelY());
    for (int i = 0; i < 512; ++i)
    {
        io.KeysDown[i] = eventManager().keyboard().scancode(static_cast<ample::control::KeyboardManager::scancodes>(i));
    }
    io.KeyShift = eventManager().keyboard().modificators().shift();
    io.KeyAlt = eventManager().keyboard().modificators().alt();
    io.KeyCtrl = eventManager().keyboard().modificators().ctrl();
    if (eventManager().keyboard().getChar())
    {
        io.AddInputCharacter(eventManager().keyboard().getChar());
    }
    if (eventManager().keyboard().isKeyDown(control::keysym::KEY_q))
    {
        DEBUG("Yes!");
    }
}

void ImguiActivity::presentGUI()
{
    ImGui::ShowDemoWindow();
    ImGui::ShowStyleEditor();
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
