#include "SliceManager.h"

namespace ample::gui
{
void SliceManager::drawInterface()
{
    ImGui::Begin("Level manager");
    if (ImGui::TreeNode("Slices"))
    {
        for (auto &[id, slice] : _currentLevel->layers())
        {
            if (ImGui::TreeNode(("slice " + std::to_string(id)).c_str()))
            {
                for (auto &obj : slice->objects())
                {
                    if (ImGui::TreeNode("object"))
                    {
                        ImGui::Text("hello!");
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
    ImGui::End();
}

void SliceManager::setLevel(std::shared_ptr<game::game2d::Level> level)
{
    _currentLevel = level;
}
} // namespace ample::gui
