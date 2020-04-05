#include "ImguiActivity.h"
#include "AmpleGui.h"
#include "ample/RegularPolygon.h"
#include "ample/WorldObject2d.h"

namespace ample::gui
{
AmpleGui::AmpleGui(ample::window::Window &window)
    : ImguiActivity(window),
      _observer(eventManager())
{
    auto &level = createLevel(1, 10.0f, 0.5f);
    setCurrentLevel(1);
    addBehaviour(_observer);
    level.camera().setVisibility(false);
    level.frontSlice().addCamera(_observer.getCamera());
    level.frontSlice().addObject(_observer.getLamp());
    Editor::instance().setCurrentLayer(level.frontSlice());
}

void AmpleGui::onResize()
{
    ImguiActivity::onResize();
    _observer.onWindowResized({static_cast<int>(getWidth()), static_cast<int>(getHeight())});
}

void AmpleGui::drawInterface()
{
    ImguiActivity::drawInterface();
    Editor::instance().drawInterface();
}
} // namespace ample::gui
