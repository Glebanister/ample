#include "objects/TransitionGui.h"
#include "ObjectStorageGui.h"
#include "Utils.h"

namespace ample::gui
{
TransitionGui::TransitionGui(std::shared_ptr<filing::NamedObject> obj, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor), _objectStorageGui(storage),
      _baseTransition(std::dynamic_pointer_cast<game::StateMachine::Transition>(obj))
{
    ASSERT(_baseTransition->getNextState());
    _nextState = _baseTransition->getNextState();
}

TransitionGui::TransitionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage)
{
}

std::shared_ptr<game::StateMachine::Transition> TransitionGui::getBaseTransition() const noexcept
{
    return _baseTransition;
}

void TransitionGui::onCreate()
{
    if (!_levelPresetted)
    {
        gui_utils::NamedObjectSelector("Level", _level, _game2dEditor->getLevelsList());
        if (_level)
        {
            gui_utils::NamedObjectSelector("State Machine", _stateMachine, _level->stateMachines());
            if (_stateMachine)
            {
                gui_utils::NamedObjectSelector("Next State",
                                               _nextState,
                                               _objectStorageGui->statesList(_stateMachine->name()));
            }
        }
    }
    else if (!_nextStatePresetted)
    {
        ASSERT(_stateMachine);
        gui_utils::NamedObjectSelector("Next State",
                                       _nextState,
                                       _objectStorageGui->statesList(_stateMachine->name()));
    }
}

void TransitionGui::presetNextState(std::shared_ptr<game::StateMachine::State> nextState) noexcept
{
    _nextState = nextState;
    _nextStatePresetted = true;
    _levelPresetted = true;
}

void TransitionGui::presetStateMachine(std::shared_ptr<game::StateMachine> machine) noexcept
{
    _stateMachine = machine;
    _levelPresetted = true;
}
} // namespace ample::gui
