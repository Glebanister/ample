#include <imgui.h>

#include "LevelBrowser.h"
#include "TextureManager.h"

namespace ample::gui
{
void LevelBrowser::drawInterface()
{
    ImGui::Text("Level browser");

    // TODO

    if (ImGui::CollapsingHeader("Textures"))
    {
        TextureManager::instance().drawInterface();
    }
}
} // namespace ample::gui
