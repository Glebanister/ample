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
    : ImguiActivity(
          "ample",
          0,
          0,
          1920 / 1.5,
          1080 / 1.5,
          ample::window::CENTERED_X | ample::window::CENTERED_Y,
          ample::window::MINIMIZED | ample::window::RESIZABLE)
{
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
        if (!_game2dEditor)
        {
            ProjectOpener();
        }
        else
        {
            Workspace();
        }
    }
    PathSelector();
    _messagePopup.drawInterface();
    if (_status)
    {
        _filebrowser.Display();
    }
    ImGui::End();
}

void AmpleGui::saveProjectAs(const std::filesystem::path &path)
{
    ASSERT(_game2dEditor);
    _game2dEditor->setProjectPath(path);
    try
    {
        _game2dEditor->save();
    }
    catch (const std::exception &e)
    {
        _messagePopup = {"Can't save prject", e.what(), true};
    }
}

void AmpleGui::saveProject()
{
    ASSERT(_game2dEditor);
    saveProjectAs(_game2dEditor->getProjectPath());
}

void AmpleGui::openProject(const std::filesystem::path &path)
{
    try
    {
        if (_game2dEditor)
        {
            _game2dEditor->save();
        }
        _game2dEditor = std::make_shared<game::game2d::Game2dEditor>(path);
        _objectsGui = std::make_shared<ObjectStorageGui>(_game2dEditor);
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
        _game2dEditor = std::make_shared<game::game2d::Game2dEditor>();
        _objectsGui = std::make_shared<ObjectStorageGui>(_game2dEditor);
        _game2dEditor->setProjectPath(path);
    }
    catch (const std::exception &e)
    {
        _messagePopup = {"Can't create new project", e.what(), true};
    }
}

void AmpleGui::usePathSelector(status s)
{
    if (!s)
        return;
    _filebrowser.Open();
    _status = s;
}

void AmpleGui::PathSelector()
{
    if (!_status)
    {
        return;
    }

    std::filesystem::path path;
    if (_filebrowser.HasSelected())
    {
        path = _filebrowser.GetSelected();
    }
    else
    {
        return;
    }

    switch (_status)
    {
    case CREATING:
        createNewProject(path);
        break;

    case OPENING:
        openProject(path);
        break;

    case SAVING_AS:
        saveProjectAs(path);
        break;

    case NOT_STARTED:
        ASSERT(false);
    }
    _status = NOT_STARTED;
}

void AmpleGui::ProjectOpener()
{
    if (ImGui::Selectable("Create new project"))
    {
        usePathSelector(CREATING);
    }

    if (ImGui::Selectable("Open existing project"))
    {
        usePathSelector(OPENING);
    }
}

void AmpleGui::MenuBar()
{
    if (ImGui::BeginMenu("Project"))
    {
        if (ImGui::MenuItem("Save project"))
        {
            saveProject();
        }
        if (ImGui::MenuItem("Save project as"))
        {
            usePathSelector(SAVING_AS);
        }
        if (ImGui::MenuItem("New project"))
        {
            usePathSelector(CREATING);
        }
        if (ImGui::MenuItem("Open project"))
        {
            usePathSelector(OPENING);
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
        ImGui::Selectable("No");
        ImGui::Selectable("Help");
        ImGui::EndMenu();
    }
}

void AmpleGui::Workspace()
{
    if (ImGui::BeginMenuBar())
    {
        MenuBar();
        ImGui::EndMenuBar();
    }
    ImGui::Columns(3, "Workspace");

    ImGui::BeginChild("Left");
    if (ImGui::CollapsingHeader("Browser", NULL, 0))
    {
        _objectsGui->browser();
    }
    if (ImGui::CollapsingHeader("Editor"))
    {
        _objectsGui->editor();
    }
    ImGui::EndChild();
    ImGui::NextColumn();

    ImGui::BeginChild("Viewer");
    _objectsGui->viewer();
    ImGui::EndChild();
    ImGui::NextColumn();

    ImGui::BeginChild("Right");
    if (ImGui::CollapsingHeader("Creator"))
    {
        _objectsGui->creator();
    }
    if (ImGui::CollapsingHeader("Inspector"))
    {
        _objectsGui->inspector();
    }
    if (ImGui::CollapsingHeader("Textures"))
    {
        _objectsGui->texturesViewer();
    }
    ImGui::EndChild();
    ImGui::NextColumn();
}
} // namespace ample::gui
