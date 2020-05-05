#pragma once

#include "ample/Level.h"

#include "TabEditor.h"

namespace ample::gui
{
class LevelEditor : public TabObjectEditor<game::game2d::Level>
{
public:
    using TabObjectEditor<game::game2d::Level>::TabObjectEditor;

    void drawInterface() override;
};
} // namespace ample::gui
