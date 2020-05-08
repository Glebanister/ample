#include <imgui.h>

#include "Utils.h"
#include "objects/StateMachineGui.h"

namespace ample::gui
{
StateMachineGui::StateMachineGui(std::shared_ptr<filing::NamedObject> sm, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor), _objectStorageGui(storage),
      _stateMachine(std::dynamic_pointer_cast<game::StateMachine>(sm))
{
}

StateMachineGui::StateMachineGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage)
{
}

void StateMachineGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    if (ImGui::Button("Level"))
    {
        ImGui::OpenPopup("Level.popup");
    }
    ImGui::SameLine();
    if (selectedLevel)
    {
        ImGui::Text("%s", selectedLevel->name().c_str());
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
                selectedLevel = level;
            }
        }
        ImGui::EndPopup();
    }
}

void StateMachineGui::onSubmitCreate()
{
    if (!selectedLevel)
    {
        throw game::GameException("Level is not selected");
    }
    _stateMachine = _game2dEditor->createStateMachine(nameBuffer, selectedLevel);
}

void StateMachineGui::onEdit()
{
}

void StateMachineGui::onSubmitEdit()
{
}

void StateMachineGui::onView()
{
}

void StateMachineGui::onInspect()
{
    ASSERT(_stateMachine);
    for (auto &state : game::getStatesList(*_stateMachine))
    {
        // if (auto stateGui = _objectStorageGui->objectGuiByName(state->name());
        //     ImGui::TreeNode(stateGui->name().c_str()))
        // {
        //     _objectStorageGui->inspectSingleItem(stateGui);
        //     stateGui->onInspect();
        //     ImGui::TreePop();
        // }
    }
}

void StateMachineGui::onPreview()
{
    ASSERT(_stateMachine);
    ImGui::Text("%s", _stateMachine->name().c_str());
}

std::string StateMachineGui::name() const
{
    ASSERT(_stateMachine);
    return _stateMachine->name();
}
std::string StateMachineGui::className() const
{
    return "StateMachine";
}
} // namespace ample::gui
