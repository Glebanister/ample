#include <imgui.h>
#include <imnodes.h>

#include "Utils.h"
#include "objects/StateGui.h"

namespace ample::gui
{
class StateGui;
StateGui::StateGui(std::shared_ptr<filing::NamedObject> state, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor), _objectStorageGui(storage),
      _state(std::dynamic_pointer_cast<game::StateMachine::State>(state))
{
}

StateGui::StateGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage)
{
}

void StateGui::presetStateMachine(std::shared_ptr<game::StateMachine> sm) noexcept
{
    _stateMachine = sm;
}

std::shared_ptr<game::StateMachine::State> StateGui::getState() const noexcept
{
    return _state;
}

void StateGui::onCreate()
{
    ASSERT(_stateMachine);
    ImGui::InputText("Name", nameBuffer, 255);
}

void StateGui::onSubmitCreate()
{
    ASSERT(_stateMachine);
    _state = std::make_shared<game::StateMachine::State>(*_stateMachine, nameBuffer);
}

void StateGui::onEdit()
{
    if (ImGui::TreeNode("Add on start action"))
    {
        for (const auto &[trName, trId] : classIdByClassName)
        {
            if (trId.parentClass != "Action")
            {
                continue;
            }
            if (ImGui::Selectable(trName.c_str()))
            {
                _objectStorageGui->create(trId.finalClass, false, [&](std::shared_ptr<ObjectGui> gui) {
                    auto actionGui = std::dynamic_pointer_cast<ActionGui>(gui);
                    _state->addOnStartAction(actionGui->getAction());
                    actionGui->getAction()->getNamespacePointer()->setParentalNamespace(_state->getStateMachine().getNamespacePointer());
                });
            }
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Add on active action"))
    {
        for (const auto &[trName, trId] : classIdByClassName)
        {
            if (trId.parentClass != "Action")
            {
                continue;
            }
            if (ImGui::Selectable(trName.c_str()))
            {
                _objectStorageGui->create(trId.finalClass, false, [&](std::shared_ptr<ObjectGui> gui) {
                    auto actionGui = std::dynamic_pointer_cast<ActionGui>(gui);
                    _state->addOnActiveAction(actionGui->getAction());
                    actionGui->getAction()->getNamespacePointer()->setParentalNamespace(_state->getStateMachine().getNamespacePointer());
                });
            }
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Add on stop action"))
    {
        for (const auto &[trName, trId] : classIdByClassName)
        {
            if (trId.parentClass != "Action")
            {
                continue;
            }
            if (ImGui::Selectable(trName.c_str()))
            {
                _objectStorageGui->create(trId.finalClass, false, [&](std::shared_ptr<ObjectGui> gui) {
                    auto actionGui = std::dynamic_pointer_cast<ActionGui>(gui);
                    _state->addOnStopAction(actionGui->getAction());
                    actionGui->getAction()->getNamespacePointer()->setParentalNamespace(_state->getStateMachine().getNamespacePointer());
                });
            }
        }
        ImGui::TreePop();
    }
}

void StateGui::onSubmitEdit()
{
}

void StateGui::onView()
{
}

void StateGui::onInspect()
{
    ASSERT(_state);
    ImGui::TextColored({0, 1, 0, 1}, "%s", "Start");
    for (auto &act : _state->getOnStartActions())
    {
        if (auto actGui = _objectStorageGui->objectGuiByName(act->name());
            ImGui::TreeNode(actGui->name().c_str()))
        {
            _objectStorageGui->inspectSingleItem(actGui);
            ImGui::TreePop();
        }
    }
    ImGui::TextColored({0, 0, 1, 1}, "%s", "Active");
    for (auto &act : _state->getOnActiveActions())
    {
        if (auto actGui = _objectStorageGui->objectGuiByName(act->name());
            ImGui::TreeNode(actGui->name().c_str()))
        {
            _objectStorageGui->inspectSingleItem(actGui);
            ImGui::TreePop();
        }
    }
    ImGui::TextColored({1, 0, 0, 1}, "%s", "Stop");
    for (auto &act : _state->getOnStopActions())
    {
        if (auto actGui = _objectStorageGui->objectGuiByName(act->name());
            ImGui::TreeNode(actGui->name().c_str()))
        {
            _objectStorageGui->inspectSingleItem(actGui);
            ImGui::TreePop();
        }
    }
    ImGui::Text("%s", "Transitions");
    for (auto &tr : _state->transitions())
    {
        if (auto trGui = _objectStorageGui->objectGuiByName(tr->name());
            ImGui::TreeNode(trGui->name().c_str()))
        {
            _objectStorageGui->inspectSingleItem(trGui);
            ImGui::TreePop();
        }
    }
}

void StateGui::onPreview()
{
    ASSERT(_state);
}

std::string StateGui::name() const
{
    ASSERT(_state);
    return _state->name();
}
std::string StateGui::className() const
{
    return "State";
}
} // namespace ample::gui
