#include <memory>

#include "AmpleGui.h"
#include "ImguiActivity.h"
#include "ample/KeyboardTransition.h"
#include "ample/RegularPolygon.h"
#include "ample/TimerTransition.h"
#include "ample/WorldObject2d.h"

#include "Editor.h"
#include "SliceManager.h"
#include "TextureManager.h"

namespace ample::gui
{
AmpleGui::AmpleGui(ample::window::Window &window)
    : ImguiActivity(window),
      _observer(std::make_shared<Observer>(*this))
{
    addBehavior(_observer);
}

AmpleGui::AmpleGui(ample::window::Window &window,
                   const std::filesystem::path &existingProjectPath)
    : ImguiActivity(window, existingProjectPath),
      _observer(std::make_shared<Observer>(*this))
{
    addBehavior(_observer);
    Editor::instance().setCurrentLayer(getCurrentLevel()->frontSlice());
    SliceManager::instance().setLevel(getCurrentLevel());
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

void AmpleGui::drawInterface()
{
    // ImguiActivity::drawInterface();
    Editor::instance().drawInterface();
    SliceManager::instance().drawInterface();
    TextureManager::instance().drawInterface();
}
} // namespace ample::gui
