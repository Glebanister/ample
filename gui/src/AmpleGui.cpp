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
      _editor(*this)
{
}

AmpleGui::AmpleGui(ample::window::Window &window,
                   const std::filesystem::path &existingProjectPath)
    : ImguiActivity(window, existingProjectPath),
      _editor(*this)
{
}

void AmpleGui::MenuBar()
{
    std::string savingError;
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Save", NULL, false, !getProjectPath().empty()))
        {
            try
            {
                save();
            }
            catch (const std::exception &e)
            {
                ImGui::OpenPopup("Save unsuccessful");
                savingError = e.what();
            }
        }
        if (ImGui::MenuItem("Save as"))
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
                _editor.openTabCreator(Editor::tabClass::STATE_MACHINE);
            }
            if (ImGui::MenuItem("Level"))
            {
                _editor.openTabCreator(Editor::tabClass::LEVEL);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    gui_utils::MessagePopup("Save unsuccessful", savingError);
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
    ImGui::SetNextWindowBgAlpha(0.0f);
    if (ImGui::Begin("Ample",
                     NULL,
                     ImGuiWindowFlags_MenuBar |
                         ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_NoSavedSettings))
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

        ImGui::SetNextWindowBgAlpha(1.0f);
        ImGui::BeginChild("Browser");
        Browser::instance().drawInterface();
        ImGui::EndChild();
        ImGui::NextColumn();

        ImGui::BeginChild("Editor");
        _editor.drawInterface();
        ImGui::EndChild();
        ImGui::GetColumnWidth();
        ImGui::NextColumn();

        Observer::instance().setViewport({ImGui::GetColumnWidth(1), ImGui::GetWindowHeight() - 50},
                                         {ImGui::GetColumnWidth(0), 0});
    }
    ImGui::End();
}
} // namespace ample::gui