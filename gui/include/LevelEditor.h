#pragma once

#include "ample/Level.h"

#include "TabEditor.h"
#include "Observer.h"

namespace ample::gui
{
class LevelEditor : public TabObjectEditor<game::game2d::Level>
{
public:
    using TabObjectEditor<game::game2d::Level>::TabObjectEditor;

    void drawInterface() override;

private:
    Observer _observer;
};
} // namespace ample::gui
