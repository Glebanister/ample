#include <imgui.h>

#include "ample/Utils.h"
#include "Utils.h"

#include "objects/SliceGui.h"

namespace ample::gui
{
SliceGui::SliceGui(std::shared_ptr<filing::NamedObject> slice, std::shared_ptr<game::game2d::Game2dEditor> editor)
    : _slice(std::dynamic_pointer_cast<filing::Scene2d>(slice)),
      _game2dEditor(editor)
{
    ASSERT(_game2dEditor); 
}

SliceGui::SliceGui(std::shared_ptr<game::game2d::Game2dEditor> editor) 
    : _game2dEditor(editor)
{
    ASSERT(_game2dEditor);
}

void SliceGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    gui_utils::InputScalar("Num", static_cast<int32_t &>(num), static_cast<int32_t>(1));

    levelSelection();
}

void SliceGui::onSubmitCreate()
{
    _slice = _level->createSlice(num, nameBuffer);
}

void SliceGui::onEdit()
{
}
void SliceGui::onSubmitEdit()
{
}
void SliceGui::onView()
{
}
void SliceGui::onInspect()
{
}

void SliceGui::onPreview()
{
    ImGui::Text("Name: %s", name().c_str());
    ImGui::Text("Num: %d", num);
}

std::string SliceGui::name() const
{
    ASSERT(_slice);
    return _slice->name();
}
std::string SliceGui::className() const
{
    return "Scene2d";
}

void SliceGui::levelSelection() 
{
    if (ImGui::Button("Level"))
    {
        ImGui::OpenPopup("Level.popup");
    }
    ImGui::SameLine();
    if (_level)
    {
        ImGui::Text("%s", _level->name().c_str());
    }
    else
    {
        gui_utils::TextDisabled("[select level]");
    }

    if (ImGui::BeginPopup("Level.popup"))
    {
        if (_game2dEditor->getLevelsList().empty())
        {
            gui_utils::TextDisabled("[empty]");
        }
        for (auto level : _game2dEditor->getLevelsList())
        {
            if (ImGui::Selectable(level->name().c_str()))
            {
                _level = level;
            }
        }
        ImGui::EndPopup();
    }
}
} // namespace ample::gui
