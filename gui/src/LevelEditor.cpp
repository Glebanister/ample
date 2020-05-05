#include <imgui.h>

#include "LevelEditor.h"

namespace ample::gui
{
LevelEditor::LevelEditor(std::shared_ptr<game::game2d::Level> level)
    : TabEditor(level) {}

void LevelEditor::drawInterface()
{
    ImGui::Text("Level editor");

    // TODO
}
} // namespace ample::gui
