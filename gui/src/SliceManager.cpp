#include "SliceManager.h"

namespace ample::gui
{
void SliceManager::drawInterface()
{
    ImGui::Begin("Level manager");
    
    ImGui::End();
}

void SliceManager::setLevel(std::shared_ptr<game::game2d::Level> level)
{
    _currentLevel = level;
}
} // namespace ample::gui
