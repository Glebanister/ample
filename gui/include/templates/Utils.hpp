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
    ImGui::InputScalar(label.c_str(), ImGuiDataType_Float, &value, &step);
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
    InputScalar(label + " y", valueY, step);
}

template <typename T>
inline void InputCoordinates(const std::string &label, T &valueX, T &valueY, T step, T min, T max)
{
    InputScalar(label + " x", valueX, step, min, max);
    InputScalar(label + " y", valueY, step, min, max);
}

template <typename T>
inline void NamedObjectSelector(const std::string &label, std::shared_ptr<T> &object, const std::vector<std::shared_ptr<T>> &list)
{
    if (ImGui::Button(label.c_str()))
    {
        ImGui::OpenPopup((label + ".popup").c_str());
    }
    ImGui::SameLine();
    if (object)
    {
        ImGui::Text("%s", object->name().c_str());
    }
    else
    {
        gui_utils::TextDisabled("[select]");
    }
    if (ImGui::BeginPopup((label + ".popup").c_str()))
    {
        if (list.empty())
        {
            gui_utils::TextDisabled("[empty]");
        }
        for (auto obj : list)
        {
            if (ImGui::Selectable(obj->name().c_str()))
            {
                object = obj;
            }
        }
        ImGui::EndPopup();
    }
}

template <typename T>
void NamedObjectSelector(const std::string &label, std::shared_ptr<T> &object, const std::unordered_map<size_t, std::shared_ptr<T>> &list)
{
    if (ImGui::Button(label.c_str()))
    {
        ImGui::OpenPopup((label + ".popup").c_str());
    }
    ImGui::SameLine();
    if (object)
    {
        ImGui::Text("%s", object->name().c_str());
    }
    else
    {
        gui_utils::TextDisabled("[select]");
    }
    if (ImGui::BeginPopup((label + ".popup").c_str()))
    {
        if (list.empty())
        {
            gui_utils::TextDisabled("[empty]");
        }
        for (auto &[id, obj] : list)
        {
            if (ImGui::Selectable((std::to_string(id) + ' ' + obj->name()).c_str()))
            {
                object = obj;
            }
        }
        ImGui::EndPopup();
    }
}
} // namespace ample::gui::gui_utils
