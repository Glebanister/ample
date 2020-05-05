#pragma once

#include <algorithm>

#include <imgui.h>
#include <string>

#include "Utils.h"

namespace ample::gui
{
template <class Param, typename... Args>
typename ObjectConstructor::ParamsAdder &ObjectConstructor::ParamsAdder::add(Args... args)
{
    _list.emplace_back(std::make_unique<Param>(args...));
    return *this;
}

template <class Creator>
void ObjectConstructor::drawInterface(const Creator &creator)
{
    std::for_each(_params.begin(), _params.end(), [](auto &param) { param->imguiInput(); });

    if (ImGui::Button("Create"))
    {
        try
        {
            creator(_params);
            _success = true;
            std::for_each(_params.begin(), _params.end(), [](auto &param) { param->reset(); });
        }
        catch (const std::exception &e)
        {
            ImGui::OpenPopup("Creation failed");
            _errorString = e.what();
        }
    }
    gui_utils::MessagePopup("Creation failed", _errorString);
    ImGui::SameLine();
    gui_utils::CloseCurrentPopupOnSuccessButton(_success);
}

namespace param
{
template <>
inline int value(Parameter &p)
{
    return dynamic_cast<Int &>(p).value;
}

template <>
inline float value(Parameter &p)
{
    return dynamic_cast<Float &>(p).value;
}

template <>
inline std::string value(Parameter &p)
{
    return dynamic_cast<String &>(p).buffer;
}

template <>
inline std::shared_ptr<game::game2d::Level> value(Parameter &p)
{
    return dynamic_cast<LevelsList &>(p).selectedObject;
}
} // namespace param
} // namespace ample::gui
