#pragma once

#include <imgui.h>
#include <memory>

namespace ample::gui::gui_utils
{
template <typename T>
std::shared_ptr<T> SelectNamedObjectFromList(const std::string &selectionName,
                                             const std::vector<std::shared_ptr<T>> &list);

inline void MessagePopup(const std::string &id, const std::string &message)
{
    if (ImGui::BeginPopupModal(id.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("%s", message.c_str());
        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

inline void TextDisabled(const char *text)
{
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 0.7f), "%s", text);
}

inline void CloseCurrentPopupOnSuccessButton(bool &success)
{
    if (ImGui::Button("Close") || success)
    {
        success = false;
        ImGui::CloseCurrentPopup();
    }
}
} // namespace ample::gui::gui_utils

#include "templates/Utils.hpp"
