#include <imgui.h>
#include <imnodes.h>

#include "Utils.h"
#include "objects/StateMachineGui.h"

namespace ample::gui
{
StateMachineGui::StateMachineGui(std::shared_ptr<filing::NamedObject> sm, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor), _objectStorageGui(storage),
      _stateMachine(std::dynamic_pointer_cast<game::StateMachine>(sm)),
      _statesList(game::getStatesList(*_stateMachine)),
      _startState(_stateMachine->getCurrentState())
{
    for (auto &level : _game2dEditor->getLevelsList())
    {
        for (auto &stateMachine : level->stateMachines())
        {
            if (stateMachine->name() == sm->name())
            {
                selectedLevel = level;
                break;
            }
        }
    }
    ASSERT(selectedLevel);
    std::unordered_map<std::shared_ptr<game::StateMachine::State>, int> stateId;
    for (size_t i = 0; i < _statesList.size(); ++i)
    {
        stateId[_statesList[i]] = i;
    }
    for (const auto &state : _statesList)
    {
        for (const auto &tr : state->transitions())
        {
            _links.emplace_back(stateId[state] * 2, stateId[tr->getNextState()] * 2 + 1);
        }
    }
    _links.emplace_back(-1, stateId[_stateMachine->getCurrentState()] * 2);
    // _stateMachine->setNamespace(selectedLevel->getNamespacePointer());
}

StateMachineGui::StateMachineGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage)
{
}

std::vector<std::shared_ptr<game::StateMachine::State>> &StateMachineGui::getStatesList() noexcept
{
    return _statesList;
}

void StateMachineGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    gui_utils::NamedObjectSelector("Level", selectedLevel, _game2dEditor->getLevelsList());
}

void StateMachineGui::focusState(std::shared_ptr<game::StateMachine::State> state)
{
    _activeState = state;
}

void StateMachineGui::onSubmitCreate()
{
    if (!selectedLevel)
    {
        throw game::GameException("Level is not selected");
    }
    _stateMachine = _game2dEditor->createStateMachine(nameBuffer, selectedLevel);
    _stateMachine->setNamespace(selectedLevel->getNamespacePointer());
}

void StateMachineGui::onEdit()
{
}

void StateMachineGui::onSubmitEdit()
{
}

bool isInput(int i)
{
    return !(i & 1);
}

bool isOutput(int i)
{
    return i & 1;
}

bool isRoot(int i)
{
    return i == -1;
}

int getStateIdByLinkId(int i)
{
    return i / 2;
}

void StateMachineGui::onView()
{
    imnodes::BeginNodeEditor();

    imnodes::BeginNode(-1);
    imnodes::BeginNodeTitleBar();
    ImGui::Text("%s", _stateMachine->name().c_str());
    imnodes::EndNodeTitleBar();
    imnodes::BeginOutputAttribute(-1);
    imnodes::EndAttribute();
    imnodes::EndNode();

    for (size_t i = 0; i < _statesList.size(); ++i)
    {
        auto state = _statesList[i];
        imnodes::BeginNode(i);

        imnodes::BeginNodeTitleBar();
        ImGui::Text("%s", state->name().c_str());
        imnodes::EndNodeTitleBar();

        imnodes::BeginInputAttribute(i * 2, imnodes::PinShape_CircleFilled);
        ImGui::Text("inputs");
        imnodes::EndAttribute();

        imnodes::BeginOutputAttribute(i * 2 + 1, imnodes::PinShape_TriangleFilled);
        ImGui::Text("outputs");
        imnodes::EndAttribute();

        imnodes::EndNode();
    }

    for (size_t i = 0; i < _links.size(); ++i)
    {
        imnodes::Link(i, _links[i].first, _links[i].second);
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        ImGui::OpenPopup("Editor menu");
    }

    if (ImGui::BeginPopup("Editor menu"))
    {
        if (ImGui::Selectable("New state"))
        {
            _objectStorageGui->create(finalObjectClass::STATE, false, [&](std::shared_ptr<ObjectGui> stateGui) {
                imnodes::SetNodeScreenSpacePos(_statesList.size(), ImGui::GetMousePos());
                auto state = std::dynamic_pointer_cast<StateGui>(stateGui)->getState();
                _statesList.push_back(state);
                state->setNamespace(_stateMachine->getNamespacePointer());
            });
            std::dynamic_pointer_cast<StateGui>(_objectStorageGui->getOnInputGui())->presetStateMachine(_stateMachine);
        }
        ImGui::EndPopup();
    }
    imnodes::EndNodeEditor();

    {
        int hoveredId = -1;
        if (imnodes::IsNodeHovered(&hoveredId) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            if (hoveredId != -1)
            {
                _objectStorageGui->setFocus(_statesList[hoveredId]->name());
            }
            else
            {
                _objectStorageGui->setFocus(name());
            }
        }
    }

    if (imnodes::IsLinkCreated(&idFrom, &idTo))
    {
        if (isInput(idFrom) && isOutput(idTo))
        {
            std::swap(idTo, idFrom);
        }
        if (isRoot(idFrom) && isInput(idTo)) // Start state setting !
        {
            _stateMachine->setStartState(_statesList[getStateIdByLinkId(idTo)]);
            _links.emplace_back(idFrom, idTo);
        }
        else if (isOutput(idFrom) && isInput(idTo)) // if from is odd, to is even => from is output, to is input
        {
            stateIdFrom = getStateIdByLinkId(idFrom);
            stateIdTo = getStateIdByLinkId(idTo);
            _transitionSelector.open();
        }
    }
    _transitionSelector.drawInterface();
    if (_transitionSelector.hasResult())
    {
        _objectStorageGui->create(_transitionSelector.popResult().finalClass, false, [&](std::shared_ptr<ObjectGui> gui) {
            auto tr = std::dynamic_pointer_cast<TransitionGui>(gui)->getBaseTransition();
            _statesList[stateIdFrom]->addTransition(tr);
            _links.emplace_back(idFrom, idTo);
            tr->getNamespace().setParentalNamespace(_stateMachine->getNamespacePointer());
        });
        auto newTrGui = std::dynamic_pointer_cast<TransitionGui>(_objectStorageGui->getOnInputGui());
        newTrGui->presetNextState(_statesList[stateIdTo]);
    }
}

void StateMachineGui::onInspect()
{
    ASSERT(_stateMachine);
    for (auto &state : _statesList)
    {
        if (auto stateGui = _objectStorageGui->objectGuiByName(state->name());
            ImGui::TreeNode(stateGui->name().c_str()))
        {
            _objectStorageGui->inspectSingleItem(stateGui);
            ImGui::TreePop();
        }
    }
}

void StateMachineGui::onPreview()
{
    ASSERT(_stateMachine);
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
