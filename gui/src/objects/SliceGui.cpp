#include <imgui.h>

#include "ample/Utils.h"
#include "Utils.h"

#include "objects/SliceGui.h"

namespace ample::gui
{
SliceGui::SliceGui(std::shared_ptr<filing::NamedObject> slice, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _slice(std::dynamic_pointer_cast<filing::Scene2d>(slice)),
      _game2dEditor(editor),
      _objectStorageGui(storage)
{
    ASSERT(_game2dEditor); 
}

SliceGui::SliceGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage) 
    : _game2dEditor(editor),
    _objectStorageGui(storage)
{
    ASSERT(_game2dEditor);
}

void SliceGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    gui_utils::InputScalar("Number", static_cast<int32_t &>(num), static_cast<int32_t>(1));

    gui_utils::NamedObjectSelector("Level", _level, _game2dEditor->getLevelsList());
}

void SliceGui::onSubmitCreate()
{
    if (!_level)
    {
        throw game::GameException("Level is not selected");
    }

    _slice = _level->createSlice(num, nameBuffer);
}

void SliceGui::onEdit()
{
    ASSERT(_slice);
    gui_utils::InputCoordinates("Gravity", gravity.x, gravity.y, 0.5f);
}

void SliceGui::onSubmitEdit()
{
    ASSERT(_slice);
    _level->setGravity(gravity);
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
    ImGui::Text("Number: %d", num);
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
} // namespace ample::gui
