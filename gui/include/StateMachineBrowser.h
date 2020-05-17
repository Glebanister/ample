#pragma once

#include "ample/StateMachine.h"

#include "TabBrowser.h"

namespace ample::gui
{
class StateMachineBrowser : public TabObjectBrowser<game::StateMachine>
{
public:
    using TabObjectBrowser<game::StateMachine>::TabObjectBrowser;
    void drawInterface() override;
};
} // namespace ample::gui
