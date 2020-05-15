#include <imgui.h>
#include <imnodes.h>

#include "Utils.h"
#include "objects/StateMachineGui.h"

namespace ample::gui
{
TransitionSelector::TransitionSelector(const std::string &title)
    : _title(title) {}

void TransitionSelector::drawInterface()
{
    if (_isOpened)
    {
        ImGui::OpenPopup(_title.c_str());
    }
    if (ImGui::BeginPopupModal(_title.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        int curId = 0;
        int choosenId = 0;
        for (const auto &[name, type] : classIdByClassName)
        {
            if (type.parentClass == "Transition")
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
            if (type.parentClass == "Transition")
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

void TransitionSelector::open()
{
    _isOpened = true;
}

bool TransitionSelector::hasResult()
{
    return _has;
}

ClassInfo TransitionSelector::popResult()
{
    auto res = _result;
    _result = {};
    _has = false;
    return res;
}

StateMachineGui::StateMachineGui(std::shared_ptr<filing::NamedObject> sm, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor), _objectStorageGui(storage),
      _stateMachine(std::dynamic_pointer_cast<game::StateMachine>(sm)),
      _statesList(game::getStatesList(*_stateMachine)),
      _startState(_stateMachine->getCurrentState())
{
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
    ImGui::Text("Entry point");
    imnodes::EndNodeTitleBar();
    imnodes::BeginOutputAttribute(-1);
    imnodes::EndAttribute();
    imnodes::EndNode();

    for (size_t i = 0; i < _statesList.size(); ++i)
    {
        auto state = _statesList[i];
        ImGui::Indent(100.0f);
        imnodes::BeginNode(i);

        imnodes::BeginInputAttribute(i * 2);
        imnodes::EndAttribute();

        imnodes::BeginNodeTitleBar();
        ImGui::Text("%s", state->name().c_str());
        imnodes::EndNodeTitleBar();

        _objectStorageGui->objectGuiByName(state->name())->onInspect();
        imnodes::BeginOutputAttribute(i * 2 + 1);
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
                _statesList.push_back(std::dynamic_pointer_cast<StateGui>(stateGui)->getState());
            });
            std::dynamic_pointer_cast<StateGui>(_objectStorageGui->getOnInputGui())->presetStateMachine(_stateMachine);
        }
        ImGui::EndPopup();
    }
    imnodes::EndNodeEditor();

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
