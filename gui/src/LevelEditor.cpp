#include <imgui.h>

#include "LevelEditor.h"
#include "Observer.h"

namespace ample::gui
{
void LevelEditor::drawInterface()
{
    ImGui::Text("Level editor");
    Observer::instance().look(editorTarget());
}
} // namespace ample::gui
