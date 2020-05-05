#include <memory>

#include "AmpleGui.h"
#include "ImguiActivity.h"
#include "ample/KeyboardTransition.h"
#include "ample/OpenGLEnvironment.h"
#include "ample/RegularPolygon.h"
#include "ample/TimerTransition.h"
#include "ample/WorldObject2d.h"

#include "Browser.h"
#include "Editor.h"
#include "TextureManager.h"

namespace ample::gui
{
AmpleGui::AmpleGui(ample::window::Window &window)
    : ImguiActivity(window),
      _observer(std::make_shared<Observer>(*this))
{
    addBehavior(_observer);
    Editor::instance().setEditor(*this);
    os::environment::OpenGLEnvironment::instance().setColor({0.17f, 0.213f, 0.248f, 1.00f});
}

AmpleGui::AmpleGui(ample::window::Window &window,
                   const std::filesystem::path &existingProjectPath)
    : ImguiActivity(window, existingProjectPath),
      _observer(std::make_shared<Observer>(*this))
{
    addBehavior(_observer);
    Editor::instance().setEditor(*this);
    os::environment::OpenGLEnvironment::instance().setColor({0.17f, 0.213f, 0.248f, 1.00f});
}

std::shared_ptr<gui::Observer> AmpleGui::getObserver() const noexcept
{
    return _observer;
}

void AmpleGui::onResize()
{
    ImguiActivity::onResize();
    _observer->onWindowResized({static_cast<int>(getWidth()),
                                static_cast<int>(getHeight())});
}

void AmpleGui::MenuBar()
{
    if (ImGui::BeginMenu("File"))
    {
        ImGui::MenuItem("Save", "Ctrl+S", false, !getProjectPath().empty());
        if (ImGui::MenuItem("Save as", "Ctrl+Shift+S"))
        {
            _filebrowser.Open();
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Editor"))
    {
        if (ImGui::BeginMenu("Create tab"))
        {
            if (ImGui::MenuItem("State Machine"))
            {
                Editor::instance().openTabCreator(Editor::tabClass::STATE_MACHINE);
            }
            if (ImGui::MenuItem("Level"))
            {
                Editor::instance().openTabCreator(Editor::tabClass::LEVEL);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
        ImGui::Selectable("No");
        ImGui::Selectable("Help");
        ImGui::EndMenu();
    }
    _filebrowser.Display();
    if (_filebrowser.HasSelected())
    {
        setProjectPath(_filebrowser.GetSelected());
        _filebrowser.ClearSelected();
    }
}

void AmpleGui::drawInterface()
{
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({static_cast<float>(osWindow().getWidth()),
                              static_cast<float>(osWindow().getHeight())});
    ImGui::SetNextWindowBgAlpha(0);
    if (ImGui::Begin("Ample", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        if (ImGui::BeginMenuBar())
        {
            MenuBar();
            ImGui::EndMenuBar();
        }
        ImGui::Columns(2, "Workspace");

        static bool columnFirstTimeDrawing = true;
        if (columnFirstTimeDrawing)
        {
            columnFirstTimeDrawing = false;
            ImGui::SetColumnWidth(0, 400);
        }

        ImGui::Separator();

        ImGui::BeginChild("Browser", {0, 0});
        Browser::instance().drawInterface();
        ImGui::EndChild();
        ImGui::NextColumn();

        Editor::instance().drawInterface();
        ImGui::NextColumn();
    }
    ImGui::End();
}
} // namespace ample::gui
