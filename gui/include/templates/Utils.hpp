#pragma once

#include "ample/Utils.h"

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

template <typename T>
inline void InputScalar(const std::string &label, T &value, T step, T min, T max)
{
    InputScalar(label, value, step);
    utils::limit(value, min, max);
}

template <>
inline void InputScalar(const std::string &label, float &value, float step)
{
    InputScalar(label, value, step);
}

template <>
inline void InputScalar(const std::string &label, int32_t &value, int32_t step)
{
    ImGui::InputScalar(label.c_str(), ImGuiDataType_S32, &value, &step);
}

template <>
inline void InputScalar(const std::string &label, uint32_t &value, uint32_t step)
{
    ImGui::InputScalar(label.c_str(), ImGuiDataType_U32, &value, &step);
}

template <typename T>
inline void InputCoordinates(const std::string &label, T &valueX, T &valueY, T step)
{
    InputScalar(label + " x", valueX, step);
    ImGui::SameLine();
    InputScalar(label + "y", valueY, step);
}

template <typename T>
inline void InputCoordinates(const std::string &label, T &valueX, T &valueY, T step, T min, T max)
{
    InputScalar(label + " x", valueX, step, min, max);
    ImGui::SameLine();
    InputScalar(label + "y", valueY, step, min, max);
}
} // namespace ample::gui::gui_utils
