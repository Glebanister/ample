#include "ample/Debug.h"

#include "SliceManager.h"
#include "TextureManager.h"

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
                size_t id = 0;
                for (auto &obj : slice->objects())
                {
                    if (id == 0)
                    {
                        ++id;
                        continue;
                    }
                    if (ImGui::TreeNode(obj->name().c_str()))
                    {
                        auto go2d = std::static_pointer_cast<graphics::GraphicalObject2d>(obj);
                        if (ImGui::Button("Select face texture"))
                        {
                            ImGui::OpenPopup("face_texture_selection");
                        }
                        ImGui::SameLine();
                        ImGui::TextUnformatted(!go2d->face().texture() ? "<None>" : go2d->face().texture()->name().c_str());
                        if (ImGui::BeginPopup("face_texture_selection"))
                        {
                            for (auto texture : TextureManager::instance().textures())
                            {
                                if (ImGui::Selectable(texture->name().c_str()))
                                {
                                    go2d->face().bindTexture(texture);
                                }
                            }
                            ImGui::EndPopup();
                        }
                        if (ImGui::Button("Select side texture"))
                        {
                            ImGui::OpenPopup("side_texture_selection");
                        }
                        ImGui::SameLine();
                        ImGui::TextUnformatted(!go2d->side().texture() ? "<None>" : go2d->side().texture()->name().c_str());
                        if (ImGui::BeginPopup("side_texture_selection"))
                        {
                            for (auto texture : TextureManager::instance().textures())
                            {
                                if (ImGui::Selectable(texture->name().c_str()))
                                {
                                    go2d->side().bindTexture(texture);
                                }
                            }
                            ImGui::EndPopup();
                        }
                        ImGui::TreePop();
                    }
                    ++id;
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
