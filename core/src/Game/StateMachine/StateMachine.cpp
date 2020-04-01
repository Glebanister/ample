#include "StateMachine.h"
#include "GameException.h"

namespace ample::game
{
StateMachine::Transition::Transition(StateMachine::State &nextState)
    : _nextState(nextState) {}

void StateMachine::Transition::handleEvent()
{
    _activated = true;
}

StateMachine::State &StateMachine::Transition::getNextState() const noexcept
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

StateMachine::State::State(StateMachine &machine)
    : _machine(&machine) {}

StateMachine::State::State()
    : _machine(nullptr) {}

void StateMachine::State::setMachine(StateMachine &machine)
{
    _machine = &machine;
}

void StateMachine::State::addTransition(StateMachine::Transition &transition) noexcept
{
    _transitions.push_back(&transition);
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

StateMachine::StateMachine(State &startState)
    : _currentState(&startState)
{
    startState.onStart();
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

void StateMachine::setCurrentState(State &state)
{
    if (_currentState)
    {
        _currentState->onStop();
    }
    _currentState->onStop();
    _currentState = &state;
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
