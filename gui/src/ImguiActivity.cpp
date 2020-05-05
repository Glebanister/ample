#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <ample/Window.h>
#include <ample/WindowActivity.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_sdl.h>
#include <imgui.h>
#include <imnodes.h>

#include "ImguiActivity.h"
#include "ample/Debug.h"
#include "ample/Exception.h"

namespace ample::gui
{
void initImgui(ample::window::Window &window)
{
    const char *glsl_version = "#version 330";
    glewInit();
    ample::os::environment::OpenGLEnvironment::instance();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window.pointer(), window.glContext());
    ImGui_ImplOpenGL3_Init(glsl_version);
    imnodes::Initialize();
    ImGui::GetIO().Fonts->AddFontFromFileTTF("gui/resources/fonts/OpenSans-Regular.ttf", 20.0f);
    os::environment::OpenGLEnvironment::instance().setColor({0.17f, 0.213f, 0.248f, 1.00f});
}

ImguiActivity::ImguiActivity(ample::window::Window &window,
                             const std::filesystem::path &existingProjectPath)
    : Game2dEditor(window, existingProjectPath)
{
    initImgui(window);
}

ImguiActivity::ImguiActivity(ample::window::Window &window)
    : Game2dEditor(window)
{
    initImgui(window);
}

void ImguiActivity::drawInterface()
{
    ImGui::ShowDemoWindow();
}

void ImguiActivity::onActive()
{
    for (auto &ev : control::EventManager::instance().events())
    {
        ImGui_ImplSDL2_ProcessEvent(&ev);
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(_window.pointer());
    ImGui::NewFrame();
    drawInterface();
    ImGui::Render();
    Game2dEditor::onActive();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImguiActivity::~ImguiActivity()
{
    imnodes::Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
} // namespace ample::gui
