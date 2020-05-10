#include <imgui.h>

#include "ample/GameException.h"

#include "StateMachineBrowser.h"

namespace ample::gui
{
void StateMachineBrowser::drawInterface()
{
    ImGui::Text("State machine browser");
}
} // namespace ample::gui
