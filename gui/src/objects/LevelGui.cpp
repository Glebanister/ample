#include <imgui.h>

#include "ample/Utils.h"

#include "ObjectStorageGui.h"
#include "Utils.h"
#include "objects/LevelGui.h"

namespace ample::gui
{
LevelGui::LevelGui(std::shared_ptr<filing::NamedObject> level, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage),
      _level(std::dynamic_pointer_cast<game::game2d::Level>(level))
{
}

LevelGui::LevelGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor), _objectStorageGui(storage)
{
}

void LevelGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    gui_utils::InputScalar("Slice thickness", thickness, 1.0f, 1.0f, 1000.0f);
    gui_utils::InputScalar("Physics layer position", physicsLayerPos, 0.1f, 0.0f, 1.0f);
    gui_utils::InputCoordinates("Gravity", gravity.x, gravity.y, 0.5f);
}

void LevelGui::onSubmitCreate()
{
    std::tie(_level, _loader) = _game2dEditor->createLevel(nameBuffer, thickness, physicsLayerPos, gravity);
}

void LevelGui::onEdit()
{
    ASSERT(_level);
    gui_utils::InputCoordinates("Gravity", gravity.x, gravity.y, 0.5f);
}

void LevelGui::onSubmitEdit()
{
    ASSERT(_level);
    _level->setGravity(gravity);
    for (auto &[id, slice] : _level->layers())
    {
        utils::ignore(id);
        slice->setGravity(gravity);
    }
}

void LevelGui::onView()
{
    ASSERT(_level);
    ImGui::BeginChild("Level view");
    _observer.setViewport({ImGui::GetWindowSize().x, ImGui::GetWindowSize().y - 24},
                          {ImGui::GetWindowPos().x, 7});
    _observer.look(_level);
    bool isActive = true;
    if (ImGui::IsAnyItemActive())
        isActive = false;
    if (ImGui::IsItemActive())
        isActive = true;
    if (isActive)
        _observer.updatePos();
    ImGui::EndChild();
}

void LevelGui::onInspect()
{
    ASSERT(_level);
    if (ImGui::TreeNode("Slices"))
    {
        for (auto &[id, slice] : _level->layers())
        {
            // if (auto sliceGui = _game2dEditor->objectGuiByName(slice->name());
            //     ImGui::TreeNode(sliceGui->name().c_str()))
            // {
            //     ObjectStorageGui::instance().inspectSingleItem(sliceGui);
            //     sliceGui->onInspect();
            //     ImGui::TreePop();
            // }
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("State Machines"))
    {
        for (auto &stateMachine : _level->stateMachines())
        {
            if (auto smGui = _objectStorageGui->objectGuiByName(stateMachine->name());
                ImGui::TreeNode(smGui->name().c_str()))
            {
                _objectStorageGui->inspectSingleItem(smGui);
                smGui->onInspect();
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
}

void LevelGui::onPreview()
{
    ImGui::Text("Name: %s", name().c_str());
    ImGui::Text("Slice thickness: %.2f", thickness);
    ImGui::Text("Physics layer position: %.2f", physicsLayerPos);
    ImGui::Text("Gravity x: %.2f \nGravity y: %.2f", gravity.x, gravity.y);
}

std::string LevelGui::name() const
{
    ASSERT(_level);
    return _level->name();
}
std::string LevelGui::className() const
{
    return "Level";
}
} // namespace ample::gui
