#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/StateMachine.h"

#include "InterfaceUnit.h"
#include "ObjectGui.h"
#include "ObjectStorageGui.h"

namespace ample::gui
{
class ObjectStorageGui;
class ObjectGui;

class StateMachineGui : public ObjectGui
{
public:
    StateMachineGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    StateMachineGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

    void onCreate() override;
    void onSubmitCreate() override;
    void onEdit() override;
    void onSubmitEdit() override;
    void onView() override;
    void onInspect() override;
    void onPreview() override;

    std::string name() const override;
    std::string className() const override;

    std::vector<std::shared_ptr<game::StateMachine::State>> &getStatesList() noexcept;

    void focusState(std::shared_ptr<game::StateMachine::State>); // TODO

private:
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    ObjectStorageGui *_objectStorageGui;
    gui_utils::ClassSelector _transitionSelector{"Select transition class", "Transition"};

    std::shared_ptr<game::StateMachine> _stateMachine;

    char nameBuffer[255];
    std::shared_ptr<game::game2d::Level> selectedLevel;
    int idTo, idFrom;
    int stateIdFrom, stateIdTo;
    std::vector<std::pair<int, int>> _links = {};

    std::vector<std::shared_ptr<game::StateMachine::State>> _statesList;
    std::shared_ptr<game::StateMachine::State> _startState = nullptr;
    std::shared_ptr<game::StateMachine::State> _activeState = nullptr;
};
} // namespace ample::gui
