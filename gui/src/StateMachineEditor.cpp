#include <imgui.h>

#include "StateMachineEditor.h"

namespace ample::gui
{
StateMachineEditor::StateMachineEditor(std::shared_ptr<game::StateMachine> machine)
    : TabEditor(machine) {}

void StateMachineEditor::drawInterface()
{
    ImGui::Text("State machine editor");

    // TODO
}
} // namespace ample::gui
