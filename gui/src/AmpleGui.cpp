#include <memory>

#include "ImguiActivity.h"
#include "AmpleGui.h"
#include "ample/RegularPolygon.h"
#include "ample/WorldObject2d.h"
#include "ample/TimerTransition.h"

#include "Editor.h"
#include "SliceManager.h"
#include "TextureManager.h"

namespace ample::gui
{
AmpleGui::AmpleGui(ample::window::Window &window)
    : ImguiActivity(window),
      _observer(std::make_shared<Observer>(*this))
{
    addBehavior(std::static_pointer_cast<Behavior>(_observer));
    firstLevel = Game2d::createLevel("first", 10.0f, 0.5f, {0.0f, -10.0f});
    setCurrentLevel(firstLevel);
    Editor::instance().setCurrentLayer(firstLevel->frontSlice());
    SliceManager::instance().setLevel(firstLevel);
    auto secondLevel = Game2d::createLevel("second", 10.0f, 0.5f, {0.0f, 10.0f});
    secondLevel->addTransition(std::make_shared<ample::game::TimerTransition>("transition_name1", firstLevel, 3000));
    firstLevel->addTransition(std::make_shared<ample::game::TimerTransition>("transition_name2", secondLevel, 3000));
}

std::shared_ptr<gui::Observer> AmpleGui::getObserver() const noexcept
{
    return _observer;
}

void AmpleGui::onResize()
{
    ImguiActivity::onResize();
    _observer->onWindowResized({static_cast<int>(getWidth()), static_cast<int>(getHeight())});
}

void AmpleGui::drawInterface()
{
    // ImguiActivity::drawInterface();
    Editor::instance().drawInterface();
    SliceManager::instance().drawInterface();
    TextureManager::instance().drawInterface();
}

AmpleGui::~AmpleGui()
{
    std::cout << firstLevel->frontSlice()->dump() << std::endl;
}
} // namespace ample::gui
