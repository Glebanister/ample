#include "Utils.h"
#include "ObjectStorageGui.h"

namespace ample::gui::gui_utils
{
ClassSelector::ClassSelector(const std::string &title, const std::string &parentClassName)
    : _title(title), _parentClassName(parentClassName) {}

void ClassSelector::drawInterface()
{
    if (_isOpened)
    {
        ImGui::OpenPopup(_title.c_str());
    }
    if (ImGui::BeginPopupModal(_title.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        int curId = 0;
        for (const auto &[name, type] : classIdByClassName)
        {
            if (type.parentClass == _parentClassName)
            {
                if (ImGui::RadioButton(name.c_str(), &choosenId, curId++))
                {
                    _result = type;
                }
            }
        }
        curId = 0;
        for (const auto &[name, type] : classIdByClassName)
        {
            if (type.parentClass == _parentClassName)
            {
                if (curId++ == choosenId)
                {
                    _result = type;
                }
            }
        }
        if (ImGui::Button("Close"))
        {
            _isOpened = false;
            _has = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Submit"))
        {
            _isOpened = false;
            _has = true;
        }
        ImGui::EndPopup();
    }
}

void ClassSelector::open()
{
    _isOpened = true;
}

bool ClassSelector::hasResult()
{
    return _has;
}

ClassInfo ClassSelector::popResult()
{
    auto res = _result;
    _result = {};
    _has = false;
    return res;
}

void inputKeysym(const std::string &label, control::keysym &key)
{
    ImGui::InputScalar(label.c_str(), ImGuiDataType_S16, &key);
}
} // namespace ample::gui::gui_utils
