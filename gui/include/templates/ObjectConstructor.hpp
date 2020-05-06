#pragma once

#include <algorithm>
#include <filesystem>
#include <string>

#include <imgui.h>

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
    if (_closed)
    {
        return;
    }
    if (!_modal)
    {
        ImGui::Begin(_buttonName.c_str(), NULL, _windowFlags);
    }
    std::for_each(_params.begin(), _params.end(), [](auto &param) { param->imguiInput(); });

    if (ImGui::Button(_buttonName.c_str()))
    {
        try
        {
            creator(_params);
            _success = true;
            std::for_each(_params.begin(), _params.end(), [](auto &param) { param->reset(); });
        }
        catch (const std::exception &e)
        {
            _errorPopup = {"Creation failed", e.what(), true};
        }
    }
    _errorPopup.drawInterface();
    ImGui::SameLine();
    if (_closable)
    {
        if (ImGui::Button("Close") || _success)
        {
            if (_modal)
            {
                ImGui::CloseCurrentPopup();
                _success = false;
            }
        }
    }
    if (!_modal)
    {
        ImGui::End();
    }
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

template <>
inline std::filesystem::path value(Parameter &p)
{
    return dynamic_cast<Path &>(p)._buffer;
}
} // namespace param
} // namespace ample::gui
