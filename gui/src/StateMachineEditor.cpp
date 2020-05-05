#include <imgui.h>

#include "ample/GameException.h"

#include "StateMachineEditor.h"

namespace ample::gui
{
void StateMachineEditor::drawInterface()
{
    ImGui::Text("State machine editor");
}
} // namespace ample::gui
