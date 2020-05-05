#pragma once

#include "ample/Level.h"

#include "TabBrowser.h"

namespace ample::gui
{
class LevelBrowser : public TabObjectBrowser<game::game2d::Level>
{
public:
    using TabObjectBrowser<game::game2d::Level>::TabObjectBrowser;

    void drawInterface() override;
};
} // namespace ample::gui
