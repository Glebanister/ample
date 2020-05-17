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
    _state->setNamespace(_state->getStateMachine().getNamespacePointer());
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
    if (ImGui::Selectable("Add on start action"))
    {
        _actionSelector.open();
        _actionType = 0;
    }
    if (ImGui::Selectable("Add on active action"))
    {
        _actionSelector.open();
        _actionType = 1;
    }
    if (ImGui::Selectable("Add on stop action"))
    {
        _actionSelector.open();
        _actionType = 2;
    }

    if (_actionSelector.hasResult())
    {
        auto res = _actionSelector.popResult();
        _objectStorageGui->create(res.finalClass, false, [&](std::shared_ptr<ObjectGui> gui) {
            auto actionGui = std::dynamic_pointer_cast<ActionGui>(gui);
            auto action = actionGui->getAction();
            switch (_actionType)
            {
            case 0:
                _state->addOnStartAction(action);
                break;
            case 1:
                _state->addOnActiveAction(action);
                break;
            case 2:
                _state->addOnStopAction(action);
                break;
            default:
                break;
            }
            actionGui->getAction()->getNamespacePointer()->setParentalNamespace(_state->getStateMachine().getNamespacePointer());
            actionGui->setState(_state);
            _state->setNamespace(_state->getStateMachine().getNamespacePointer());
        });
    }
}

void StateGui::onSubmitEdit()
{
}

void StateGui::onView()
{
    _objectStorageGui->objectGuiByName(_stateMachine->name())->onView();
    _actionSelector.drawInterface();
}

void StateGui::onInspect()
{
    ASSERT(_state);
    auto inspectActionsList = [&](std::vector<std::shared_ptr<game::Action>> &list) {
        for (auto &act : list)
        {
            if (auto actGui = _objectStorageGui->objectGuiByName(act->name());
                ImGui::TreeNode(actGui->name().c_str()))
            {
                _objectStorageGui->inspectSingleItem(actGui);
                ImGui::TreePop();
            }
        }
    };
    if (ImGui::TreeNode("Start"))
    {
        inspectActionsList(_state->getOnStartActions());
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Active"))
    {
        inspectActionsList(_state->getOnActiveActions());
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Stop"))
    {
        inspectActionsList(_state->getOnStopActions());
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Transitions"))
    {
        for (auto &tr : _state->transitions())
        {
            if (auto trGui = _objectStorageGui->objectGuiByName(tr->name());
                ImGui::TreeNode(trGui->name().c_str()))
            {
                _objectStorageGui->inspectSingleItem(trGui);
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
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
