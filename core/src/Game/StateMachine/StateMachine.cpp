#include <memory>

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

StateMachine::State::State(std::shared_ptr<StateMachine> machine, const std::string &name)
    : _machine(machine), _name(name) {}

StateMachine::State::State(const std::string &name)
    : _machine(std::make_shared<StateMachine>()), _name(name) {}

void StateMachine::State::setMachine(std::shared_ptr<StateMachine> machine) noexcept
{
    _machine = machine;
}

std::string StateMachine::State::getName() const noexcept
{
    return _name;
}

void StateMachine::State::addTransition(std::shared_ptr<StateMachine::Transition> transition) noexcept
{
    addBehavior(std::static_pointer_cast<Behavior>(transition));
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
    if (_currentState)
    {
        _currentState->onActive();
    }
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
