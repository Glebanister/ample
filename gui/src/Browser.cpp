#include <algorithm>

#include "Browser.h"
#include "LevelBrowser.h"
#include "StateMachineBrowser.h"

namespace ample::gui
{
void Browser::drawInterface()
{
    if (!_openedBrowsers.empty())
    {
        _openedBrowsers.at(_openedBrowserId)->drawInterface();
    }
    else
    {
        ImGui::Text("Select tab to browse");
    }
    
}

void Browser::openBrowserTab(std::shared_ptr<filing::NamedObject> object)
{
    for (size_t i = 0; i < _openedBrowsers.size(); ++i)
    {
        if (_openedBrowsers[i]->browserTargetNamedObject()->name() == object->name())
        {
            _openedBrowserId = i;
            return;
        }
    }
    if (object->className() == "Level")
    {
        _openedBrowsers.emplace_back(std::make_unique<LevelBrowser>(std::static_pointer_cast<game::game2d::Level>(object)));
    }
    else if (object->className() == "StateMachine")
    {
        _openedBrowsers.emplace_back(std::make_unique<StateMachineBrowser>(std::static_pointer_cast<game::StateMachine>(object)));
    }
}
} // namespace ample::gui
