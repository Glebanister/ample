#include <imgui.h>

#include "LevelEditor.h"
#include "Observer.h"

namespace ample::gui
{
void LevelEditor::drawInterface()
{
    ImGui::Text("Level editor");

    _observer.setViewport({ImGui::GetWindowSize().x, ImGui::GetWindowSize().y - 24},
                          {ImGui::GetWindowPos().x, 7});

    _observer.look(editorTarget());
    if (isActive())
    {
        _observer.updatePos();
    }
}
} // namespace ample::gui
