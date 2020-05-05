#pragma once

#include "Utils.h"

namespace ample::gui::gui_utils
{
template <typename T>
std::shared_ptr<T> SelectNamedObjectFromList(const std::string &selectionTitle,
                                             const std::vector<std::shared_ptr<T>> &list)
{
    if (ImGui::Button(selectionTitle.c_str()))
    {
        ImGui::OpenPopup((selectionTitle + ".popup").c_str());
    }
    ImGui::SameLine();
    if (ImGui::BeginPopup((selectionTitle + ".popup").c_str()))
    {
        for (auto object : list)
        {
            if (ImGui::Selectable(object->name().c_str()))
            {
                ImGui::EndPopup();
                return object;
            }
        }
        ImGui::EndPopup();
    }
    return nullptr;
}
} // namespace ample::gui::gui_utils
