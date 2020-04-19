#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <ample/WindowActivity.h>
#include <ample/Window.h>
#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_sdl.h>

#include "ImguiActivity.h"
#include "ample/Debug.h"
#include "ample/Exception.h"

namespace ample::gui
{
ImguiActivity::ImguiActivity(ample::window::Window &window)
        : Game2d(window)
{
    const char *glsl_version = "#version 330";
    glewInit();
    ample::os::environment::OpenGLEnvironment::instance();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window.pointer(), window.glContext());
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImguiActivity::drawInterface()
{
    ImGui::ShowDemoWindow();
}

void ImguiActivity::onActive()
{
    for (auto &ev : eventManager().events())
    {
        ImGui_ImplSDL2_ProcessEvent(&ev);
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(_window.pointer());
    ImGui::NewFrame();
    drawInterface();
    ImGui::Render();
    Game2d::onActive();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImguiActivity::~ImguiActivity()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
} // namespace ample::gui