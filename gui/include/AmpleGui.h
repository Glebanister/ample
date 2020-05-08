#pragma once

#include <optional>

#include <imgui.h> // sould be included before imfilebrowser.h

#include <imfilebrowser.h>

#include "ample/Behaviour.h"
#include "ample/Camera.h"
#include "ample/EventManager.h"
#include "ample/Game2d.h"
#include "ample/LightSource.h"
#include "ample/Window.h"
#include "ample/WorldObject2d.h"

#include "Editor.h"
#include "ImguiActivity.h"
#include "ObjectConstructor.h"
#include "ObjectStorageGui.h"
#include "Observer.h"

namespace ample::gui
{
class AmpleGui : public utils::Singleton<AmpleGui>, public ImguiActivity
{
    enum status
    {
        NOT_STARTED = 0,
        CREATING,
        OPENING,
        SAVING_AS
    };

public:
    AmpleGui();

    void drawInterface() override;

    void saveProject();
    void saveProjectAs(const std::filesystem::path &path);
    void openProject(const std::filesystem::path &path);
    void createNewProject(const std::filesystem::path &);

    void usePathSelector(status);

private:
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    std::shared_ptr<ObjectStorageGui> _objectsGui;

    void ProjectOpener();
    void MenuBar();
    void Workspace();
    void trySaveProject();
    void PathSelector();

    gui_utils::MessagePopup _messagePopup;
    ImGui::FileBrowser _filebrowser{ImGuiFileBrowserFlags_CloseOnEsc |
                                    ImGuiFileBrowserFlags_CreateNewDir |
                                    ImGuiFileBrowserFlags_SelectDirectory |
                                    ImGuiFileBrowserFlags_NoTitleBar};

    status _status = NOT_STARTED;
};
} // namespace ample::gui
