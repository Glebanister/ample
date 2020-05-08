#include <memory>

#include <imgui.h>

#include "ample/KeyboardTransition.h"
#include "ample/OpenGLEnvironment.h"
#include "ample/RegularPolygon.h"
#include "ample/TimerTransition.h"
#include "ample/WorldObject2d.h"

#include "AmpleGui.h"
#include "Browser.h"
#include "Editor.h"
#include "ImguiActivity.h"
#include "ObjectStorageGui.h"
#include "TextureManager.h"

namespace ample::gui
{
AmpleGui::AmpleGui()
    : ImguiActivity(*(new window::Window(
          "ample",
          0,
          0,
          1920 / 1.5,
          1080 / 1.5,
          ample::window::CENTERED_X | ample::window::CENTERED_Y,
          ample::window::MINIMIZED | ample::window::RESIZABLE

          )))
{
}

void AmpleGui::drawInterface()
{
    if (!_game2dEditor)
    {
        ProjectOpener();
    }
    else
    {
        Workspace();
    }
    _messagePopup.drawInterface();
    _filebrowser.Display();
}

void AmpleGui::saveProjectAs(const std::filesystem::path &path)
{
    ASSERT(_game2dEditor);
    try
    {
        _game2dEditor->saveAs(path);
    }
    catch (const std::exception &e)
    {
        _messagePopup = {"Can't save prject", e.what(), true};
    }
}

void AmpleGui::openProject(const std::filesystem::path &path)
{
    try
    {
        if (_game2dEditor)
        {
            _game2dEditor->save();
        }
        _game2dEditor = std::make_shared<game::game2d::Game2dEditor>(_window, path);
    }
    catch (const std::exception &e)
    {
        _messagePopup = {"Can't open project", e.what(), true};
    }
}

void AmpleGui::createNewProject(const std::filesystem::path &path)
{
    try
    {
        if (_game2dEditor)
        {
            _game2dEditor->save();
        }
        _game2dEditor = std::make_shared<game::game2d::Game2dEditor>(_window);
        _game2dEditor->setProjectPath(path);
    }
    catch (const std::exception &e)
    {
        _messagePopup = {"Can't create new project", e.what(), true};
    }
}

void AmpleGui::ProjectOpener()
{
    if (ImGui::Selectable("Create new project"))
    {
    }

    if (ImGui::Selectable("Open existing project"))
    {
    }
}

// void AmpleGui::MenuBar();
// void AmpleGui::Workspace();
// void AmpleGui::trySaveProject();

void AmpleGui::MenuBar()
{
    // if (ImGui::BeginMenu("File"))
    // {
    //     if (ImGui::MenuItem("Save")
    //     {
    //         trySaveProject();
    //     }
    //     if (ImGui::MenuItem("Save as"))
    //     {
    //         _filebrowser.Open();
    //     }
    //     ImGui::EndMenu();
    // }
    // if (ImGui::BeginMenu("Editor"))
    // {
    //     if (ImGui::BeginMenu("Create tab"))
    //     {
    //         if (ImGui::MenuItem("State Machine"))
    //         {
    //             _editor.openTabCreator(Editor::tabClass::STATE_MACHINE);
    //         }
    //         if (ImGui::MenuItem("Level"))
    //         {
    //             _editor.openTabCreator(Editor::tabClass::LEVEL);
    //         }
    //         ImGui::EndMenu();
    //     }
    //     ImGui::EndMenu();
    // }
    // if (ImGui::BeginMenu("Help"))
    // {
    //     ImGui::Selectable("No");
    //     ImGui::Selectable("Help");
    //     ImGui::EndMenu();
    // }
    // _filebrowser.Display();
    // if (_filebrowser.HasSelected())
    // {
    //     setProjectPath(_filebrowser.GetSelected());
    //     trySaveProject();
    //     _filebrowser.ClearSelected();
    // }
}

void AmpleGui::Workspace()
{
    // ImGui::SetNextWindowPos({0, 0});
    // ImGui::SetNextWindowSize({static_cast<float>(osWindow().getWidth()),
    //                           static_cast<float>(osWindow().getHeight())});
    // ImGui::SetNextWindowBgAlpha(0.0f);
    // if (ImGui::Begin("Ample",
    //                  NULL,
    //                  ImGuiWindowFlags_MenuBar |
    //                      ImGuiWindowFlags_NoCollapse |
    //                      ImGuiWindowFlags_NoResize |
    //                      ImGuiWindowFlags_NoTitleBar |
    //                      ImGuiWindowFlags_NoSavedSettings))
    // {

    //     if (ImGui::BeginMenuBar())
    //     {
    //         MenuBar();
    //         ImGui::EndMenuBar();
    //     }
    //     ImGui::Columns(3, "Workspace");

    //     ImGui::BeginChild("Left");
    //     if (ImGui::CollapsingHeader("Browser", NULL, 0))
    //     {
    //         _objectsGui.browser();
    //     }
    //     if (ImGui::CollapsingHeader("Editor"))
    //     {
    //         _objectsGui.editor();
    //     }
    //     ImGui::EndChild();
    //     ImGui::NextColumn();

    //     ImGui::BeginChild("Viewer");
    //     _objectsGui.viewer();
    //     ImGui::EndChild();
    //     ImGui::NextColumn();

    //     ImGui::BeginChild("Right");
    //     if (ImGui::CollapsingHeader("Creator"))
    //     {
    //         _objectsGui.creator();
    //     }
    //     if (ImGui::CollapsingHeader("Inspector"))
    //     {
    //         _objectsGui.inspector();
    //     }
    //     ImGui::EndChild();
    //     ImGui::NextColumn();
    // }
    // ImGui::End();
}
} // namespace ample::gui
