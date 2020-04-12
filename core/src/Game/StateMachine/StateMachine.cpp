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
    : NamedObject("State", name), _machine(machine) {}

StateMachine::State::State(const std::string &name)
    : NamedObject("State", name), _machine(std::make_shared<StateMachine>()) {}

void StateMachine::State::addOnStartAction(std::shared_ptr<Action> action)
{
    _onStartActions.push_back(action);
}

void StateMachine::State::addOnActiveAction(std::shared_ptr<Action> action)
{
    _onActiveActions.push_back(action);
}

void StateMachine::State::addOnStopAction(std::shared_ptr<Action> action)
{
    _onStopActions.push_back(action);
}

void StateMachine::State::setMachine(std::shared_ptr<StateMachine> machine) noexcept
{
    _machine = machine;
}

void StateMachine::State::addTransition(std::shared_ptr<StateMachine::Transition> transition) noexcept
{
    addBehavior(std::static_pointer_cast<Behavior>(transition));
    _transitions.push_back(transition);
}

void StateMachine::State::onStart()
{
    for (const auto &action : _onStartActions)
    {
        action->onActive();
    }
}

void StateMachine::State::onStop()
{
    for (const auto &action : _onStartActions)
    {
        action->onActive();
    }
}

void StateMachine::State::onActive()
{
    activity::Behavior::onActive();
    for (const auto &action : _onActiveActions)
    {
        action->onActive();
    }
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

void StateMachine::State::dumpTransitionsToVector(std::vector<std::string> &strings, filing::JsonIO output)
{
    filing::JsonIO writer("");
    std::vector<std::string> transitions;
    for (const auto &transition : _transitions)
    {
        transitions.push_back(transition -)
            writer.write<std::string>("")
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
    _startState = state;
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

std::shared_ptr<StateMachine::State> StateMachine::getCurrentState() noexcept
{
    return _currentState;
}

StateMachine::StateMachine(const std::string &name)
    : NamedObject("StateMachine", name) {}

std::string StateMachine::dump(filing::JsonIO input, const std::string &fieldName)
{
    if (!_startState)
    {
        throw GameException{"state machine start state has not been recorded, dump can not be handled"};
    }
    std::vector<std::string> statesStrings;
    input.write<std::string>("name", name());
    input.write<std::string>("start_state", _startState->name());

    _startState->dumpTransitionsToVector(statesStrings);
    return filing::makeField(fieldName, filing::mergeStrings(statesStrings));
}

StateMachine::~StateMachine()
{
    if (_currentState)
    {
        _currentState->onStop();
    }
}
} // namespace ample::game
