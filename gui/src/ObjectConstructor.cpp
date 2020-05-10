#include "ample/Utils.h"

#include "ObjectConstructor.h"
#include "Utils.h"

namespace ample::gui
{
ObjectConstructor::ParamsAdder::ParamsAdder(std::vector<std::unique_ptr<param::Parameter>> &list)
    : _list(list) {}

typename ObjectConstructor::ParamsAdder &ObjectConstructor::addParameters()
{
    return _adder;
}

ObjectConstructor::ObjectConstructor(const std::string &buttonName, bool closable, ImGuiWindowFlags_ flags, bool modal)
    : _adder(_params), _buttonName(buttonName), _closable(closable), _windowFlags(flags), _modal(modal)
{
}

namespace param
{
Parameter::Parameter(const std::string &paramName)
    : name(paramName) {}

Int::Int(const std::string &name, int cur, int min, int max, int step)
    : Parameter(name), value(cur), step(step), min(min), max(max), _begin(cur) {}

Int::Int(const std::string &name, int cur, int step)
    : Parameter(name), value(cur), step(step), unlimitedMin(true), unlimitedMax(true), _begin(cur) {}

void Int::imguiInput()
{
    ImGui::InputScalar(name.c_str(), ImGuiDataType_S32, &value, &step);
    if (!unlimitedMin)
    {
        value = std::max(min, value);
    }
    if (!unlimitedMax)
    {
        value = std::min(max, value);
    }
}

void Int::reset()
{
    value = _begin;
}

Float::Float(const std::string &name, float cur, float min, float max, float step)
    : Parameter(name), value(cur), step(step), min(min), max(max), _begin(cur) {}

Float::Float(const std::string &name, float cur, float step)
    : Parameter(name), value(cur), step(step), unlimitedMin(true), unlimitedMax(true), _begin(cur) {}

void Float::imguiInput()
{
    ImGui::InputScalar(name.c_str(), ImGuiDataType_Float, &value, &step);
    if (!unlimitedMin)
    {
        value = std::max(min, value);
    }
    if (!unlimitedMax)
    {
        value = std::min(max, value);
    }
}

void Float::reset()
{
    value = _begin;
}

String::String(const std::string &name)
    : Parameter(name)
{
}

void String::imguiInput()
{
    ImGui::InputText(name.c_str(), buffer, 255);
}

void String::reset()
{
    buffer[0] = '\0';
}

Path::Path(const std::string &name, ImGuiFileBrowserFlags_ flags)
    : Parameter(name), _filebrowser(flags) {}

void Path::imguiInput()
{
    if (ImGui::Button(name.c_str()))
    {
        _filebrowser.Open();
    }
    ImGui::SameLine();
    ImGui::Text("%s", _buffer.c_str());
    _filebrowser.Display();
    if (_filebrowser.HasSelected())
    {
        _buffer = _filebrowser.GetSelected();
    }
}

void Path::reset()
{
    _buffer.erase();
    _filebrowser.ClearSelected();
}

LevelsList::LevelsList(const std::string &name, std::vector<std::shared_ptr<game::game2d::Level>> *list)
    : Parameter(name), _list(list)
{
}

void LevelsList::imguiInput()
{
    if (ImGui::Button(name.c_str()))
    {
        ImGui::OpenPopup((name + ".popup").c_str());
    }
    ImGui::SameLine();
    if (selectedObject)
    {
        ImGui::Text("%s", selectedObject->name().c_str());
    }
    else
    {
        gui_utils::TextDisabled("[select level]");
    }

    ASSERT(_list);
    if (ImGui::BeginPopup((name + ".popup").c_str()))
    {
        if (_list->empty())
        {
            gui_utils::TextDisabled("[empty]");
        }
        for (auto object : *_list)
        {
            if (ImGui::Selectable(object->name().c_str()))
            {
                selectedObject = object;
            }
        }
        ImGui::EndPopup();
    }
}

void LevelsList::reset()
{
    selectedObject.reset();
}
} // namespace param
} // namespace ample::gui
