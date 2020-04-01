#include "StateMachine.h"
#include "GameException.h"
#include "Debug.h"

namespace ample::game
{
StateMachine::Transition::Transition(std::shared_ptr<StateMachine::State> nextState)
    : _nextState(nextState) {}

void StateMachine::Transition::handleEvent()
{
    _activated = true;
}

std::shared_ptr<StateMachine::State> StateMachine::Transition::getNextState() const noexcept
{
    return _nextState;
}

bool StateMachine::Transition::isActivated() const noexcept
{
    return _activated;
}

void StateMachine::Transition::reset() noexcept
{
    _activated = false;
}

StateMachine::State::State(std::shared_ptr<StateMachine> machine)
    : _machine(machine) {}

void StateMachine::State::addTransition(std::shared_ptr<StateMachine::Transition> transition) noexcept
{
    _transitions.push_back(transition);
}

void StateMachine::State::onActive()
{
    activity::Behavior::onActive();
    for (auto transition : _transitions)
    {
        if (!transition)
        {
            throw GameException{"invalid transition"};
        }
        transition->onActive();
        if (transition->isActivated())
        {
            transition->reset();
            if (!_machine)
            {
                throw GameException{"state machine is empty, transition can not be done"};
            }
            _machine->setCurrentState(transition->getNextState());
        }
    }
}

void StateMachine::onActive()
{
    activity::Behavior::onActive();
    if (!_currentState)
    {
        throw GameException{"state machine current state is null"};
    }
    _currentState->onActive();
}

void StateMachine::setStartState(std::shared_ptr<State> state)
{
    _currentState = state;
    _currentState->onStart();
}

void StateMachine::setCurrentState(std::shared_ptr<State> state)
{
    if (_currentState)
    {
        _currentState->onStop();
    }
    _currentState = state;
    _currentState->onStart();
}

StateMachine::~StateMachine()
{
    if (_currentState)
    {
        _currentState->onStop();
    }
}
} // namespace ample::game
