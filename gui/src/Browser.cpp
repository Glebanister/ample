#include "Browser.h"

namespace ample::gui
{
void Browser::drawInterface()
{
    ImGui::Text("This is browser");
    // if (ImGui::CollapsingHeader("Slice manager"))
    // {
    //     SliceManager::instance().drawInterface();
    // }
    // if (ImGui::CollapsingHeader("Texture manager"))
    // {
    //     TextureManager::instance().drawInterface();
    // }
    // if (ImGui::CollapsingHeader("Level manager"))
    // {
    //     LevelManager::instance().drawInterface();
    // }
}

void Browser::setFocus(std::shared_ptr<filing::NamedObject> object)
{
    _focusedObject = object;
}

filing::NamedObject &Browser::getFocusedObject() noexcept
{
    return *_focusedObject;
}
} // namespace ample::gui
