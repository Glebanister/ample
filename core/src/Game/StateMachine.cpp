#include "StateMachine.h"

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

void StateMachine::State::addTransition(StateMachine::Transition &transition) noexcept
{
    _transitions.push_back(&transition);
}

void StateMachine::State::onActive()
{
    activity::Behavior::onActive();
    for (auto transition : _transitions)
    {
        transition->onActive();
        if (transition->isActivated())
        {
            transition->reset();
            _machine.setCurrentState(transition->getNextState());
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
    _currentState->onActive();
}

void StateMachine::setCurrentState(State &state)
{
    _currentState->onStop();
    _currentState = &state;
    _currentState->onStart();
}

StateMachine::~StateMachine()
{
    _currentState->onStop();
}
} // namespace ample::game
