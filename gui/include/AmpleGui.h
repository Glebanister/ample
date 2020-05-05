#pragma once

#include <imgui.h>

#include <imfilebrowser.h>

#include "ample/Behaviour.h"
#include "ample/Camera.h"
#include "ample/EventManager.h"
#include "ample/Game2d.h"
#include "ample/LightSource.h"
#include "ample/Window.h"
#include "ample/WorldObject2d.h"

#include "ImguiActivity.h"
#include "Observer.h"

namespace ample::gui
{
class Observer;
} // namespace ample::gui

namespace ample::gui
{
class AmpleGui : public ImguiActivity
{
public:
    AmpleGui(ample::window::Window &window);
    AmpleGui(ample::window::Window &window,
             const std::filesystem::path &existingProjectPath);
    void onResize() override;
    void drawInterface() override;

    std::shared_ptr<gui::Observer> getObserver() const noexcept;

private:
    void MenuBar();
    std::shared_ptr<gui::Observer> _observer;
    ImGui::FileBrowser _filebrowser{ImGuiFileBrowserFlags_CloseOnEsc |
                                    ImGuiFileBrowserFlags_CreateNewDir |
                                    ImGuiFileBrowserFlags_SelectDirectory |
                                    ImGuiFileBrowserFlags_NoTitleBar};
};
} // namespace ample::gui
