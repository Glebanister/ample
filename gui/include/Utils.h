#pragma once

#include <imgui.h>
#include <vector>
#include <string>
#include <memory>

namespace ample::gui::gui_utils
{
template <typename T>
std::shared_ptr<T> SelectNamedObjectFromList(const std::string &selectionName,
                                             const std::vector<std::shared_ptr<T>> &list);

class MessagePopup
{
public:
    MessagePopup(const std::string &id, const std::string &message, bool opened = false)
        : id(id), message(message), opened(opened) {}

    MessagePopup() = default;

    std::string id;
    std::string message;
    bool opened = false;
    void drawInterface()
    {
        if (opened || !message.empty())
        {
            ImGui::OpenPopup(id.c_str());
            if (ImGui::BeginPopupModal(id.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("%s", message.c_str());
                if (ImGui::Button("Close"))
                {
                    message.clear();
                    opened = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
    }
};

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
template <typename T>
void InputScalar(const std::string &label, T &value, T step);

template <typename T>
void InputScalar(const std::string &label, T &value, T step, T min, T max);

template <typename T>
void InputCoordinates(const std::string &label, T &valueX, T &valueY, T step);

template <typename T>
void InputCoordinates(const std::string &label, T &valueX, T &valueY, T step, T min, T max);

template <typename T>
void NamedObjectSelector(const std::string &label, std::shared_ptr<T> &object, const std::vector<std::shared_ptr<T>> &list);
} // namespace ample::gui::gui_utils

#include "templates/Utils.hpp"
