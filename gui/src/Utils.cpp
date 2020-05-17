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

std::unordered_map<std::string, control::KeyboardManager::scancodes> keysymByName{
    {"a", control::KeyboardManager::scancodes::A},
    {"b", control::KeyboardManager::scancodes::B},
    {"c", control::KeyboardManager::scancodes::C},
    {"d", control::KeyboardManager::scancodes::D},
    {"e", control::KeyboardManager::scancodes::E},
    {"f", control::KeyboardManager::scancodes::F},
    {"g", control::KeyboardManager::scancodes::G},
    {"h", control::KeyboardManager::scancodes::H},
    {"i", control::KeyboardManager::scancodes::I},
    {"j", control::KeyboardManager::scancodes::J},
    {"k", control::KeyboardManager::scancodes::K},
    {"l", control::KeyboardManager::scancodes::L},
    {"m", control::KeyboardManager::scancodes::M},
    {"n", control::KeyboardManager::scancodes::N},
    {"o", control::KeyboardManager::scancodes::O},
    {"p", control::KeyboardManager::scancodes::P},
    {"q", control::KeyboardManager::scancodes::Q},
    {"r", control::KeyboardManager::scancodes::R},
    {"s", control::KeyboardManager::scancodes::S},
    {"t", control::KeyboardManager::scancodes::T},
    {"u", control::KeyboardManager::scancodes::U},
    {"v", control::KeyboardManager::scancodes::V},
    {"w", control::KeyboardManager::scancodes::W},
    {"x", control::KeyboardManager::scancodes::X},
    {"y", control::KeyboardManager::scancodes::Y},
    {"z", control::KeyboardManager::scancodes::Z},
    {"space", control::KeyboardManager::scancodes::C_SPACE},
    {"enter", control::KeyboardManager::scancodes::C_ENTER},
    {"lshift", control::KeyboardManager::scancodes::C_LSHIFT},
    {"rshift", control::KeyboardManager::scancodes::C_RSHIFT},
    {"lctrl", control::KeyboardManager::scancodes::C_LCTRL},
    {"rctrl", control::KeyboardManager::scancodes::C_RCTRL},
    {"lalt", control::KeyboardManager::scancodes::C_LALT},
    {"ralt", control::KeyboardManager::scancodes::C_RALT},
    {"tab", control::KeyboardManager::scancodes::C_TAB}};

void inputKeysym(const std::string &label, std::string &keyname, control::keysym &keycode)
{
    StringSelector(label, keyname, {
                                       "a",
                                       "b",
                                       "c",
                                       "d",
                                       "e",
                                       "f",
                                       "g",
                                       "h",
                                       "i",
                                       "j",
                                       "k",
                                       "l",
                                       "m",
                                       "n",
                                       "o",
                                       "p",
                                       "q",
                                       "r",
                                       "s",
                                       "t",
                                       "u",
                                       "v",
                                       "w",
                                       "x",
                                       "y",
                                       "z",
                                       "space",
                                       "enter",
                                       "lshift",
                                       "rshift",
                                       "lctrl",
                                       "rctrl",
                                       "lalt",
                                       "ralt",
                                       "tab",
                                   });
    if (keyname.length())
    {
        keycode = static_cast<control::keysym>(keysymByName[keyname]);
    }
}
} // namespace ample::gui::gui_utils
