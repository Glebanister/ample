#pragma once

#include "ample/Level.h"

#include "TabEditor.h"

namespace ample::gui
{
class LevelEditor : public TabEditor
{
public:
    LevelEditor(std::shared_ptr<game::game2d::Level>);

    void drawInterface() override;
};
} // namespace ample::gui
