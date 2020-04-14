#include <memory>
#include <iostream>
#include <numeric>

#include "StateMachine.h"
#include "GameException.h"
#include "Debug.h"
#include "Factory.h"

namespace ample::game
{
StateMachine::Transition::Transition(const std::string &name,
                                     const std::string &className,
                                     std::shared_ptr<StateMachine::State> nextState)
    : NamedStoredObject(name, className), _nextState(nextState) {}

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

std::string StateMachine::Transition::dump()
{
    filing::JsonIO output{NamedStoredObject::dump()};
    output.write<std::string>("to", _nextState->name());
    return output;
}

StateMachine::State::State(std::shared_ptr<StateMachine> machine, const std::string &name)
    : NamedStoredObject(name, "State"), _machine(machine) {}

StateMachine::State::State(const std::string &name)
    : NamedStoredObject(name, "State"), _machine(nullptr) {} // TODO: may be mistake

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

void StateMachine::State::dumpRecursive(std::vector<std::string> &strings,
                                        std::unordered_map<std::string, bool> &used)
{
    if (used[name()])
    {
        return;
    }
    used[name()] = true;
    filing::JsonIO output = dump();
    std::vector<std::string> dumpedTransitions;
    for (const auto &transition : _transitions)
    {
        dumpedTransitions.push_back(transition->dump());
    }
    output = filing::mergeStrings({output, filing::makeField("transitions", filing::dumpObjectsVector(dumpedTransitions))});
    for (const auto &transition : _transitions)
    {
        transition->getNextState()->dumpRecursive(strings, used);
    }
    strings.push_back(output);
}

StateMachine::State::State(const filing::JsonIO &input)
    : NamedStoredObject(input, "State")
{
    auto onStartActionStrings = filing::loadObjectsVector(input.read<std::string>("onStart"));
    auto onActiveActionStrings = filing::loadObjectsVector(input.read<std::string>("onActive"));
    auto onStopActionStrings = filing::loadObjectsVector(input.read<std::string>("onStop"));
    for (const auto &actionString : onStartActionStrings)
    {
        // addOnStartAction(utils::Factory<Action>())
    }
    for (const auto &actionString : onActiveActionStrings)
    {
        // addOnStartAction(utils::Factory<Action>())
    }
    for (const auto &actionString : onStopActionStrings)
    {
        // addOnStartAction(utils::Factory<Action>()) // TODO
    }
}

void StateMachine::State::addOnStartAction(std::shared_ptr<Action> action) noexcept
{
    _onStartActions.emplace_back(action);
}

void StateMachine::State::addOnActiveAction(std::shared_ptr<Action> action) noexcept
{
    _onActiveActions.emplace_back(action);
}

void StateMachine::State::addOnStopAction(std::shared_ptr<Action> action) noexcept
{
    _onStopActions.emplace_back(action);
}

std::string StateMachine::State::dump()
{
    filing::JsonIO output = NamedStoredObject::dump();
    std::vector<std::string> startActions, activeActions, stopActions;
    // TODO: it's c++2a, use iterators?
    for (const auto &act : _onStartActions)
    {
        startActions.emplace_back(act->name());
    }
    for (const auto &act : _onActiveActions)
    {
        activeActions.emplace_back(act->name());
    }
    for (const auto &act : _onStopActions)
    {
        stopActions.emplace_back(act->name());
    }
    return filing::mergeStrings({
        output.getJSONstring(),
        filing::makeField("onActive", filing::dumpObjectsVector(activeActions)),
        filing::makeField("onStart", filing::dumpObjectsVector(startActions)),
        filing::makeField("onStop", filing::dumpObjectsVector(stopActions)),
    });
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
    : NamedStoredObject(name, "StateMachine") {}

StateMachine::StateMachine(const filing::JsonIO &input)
    : NamedStoredObject(input)
{
    auto stateStrings = filing::loadObjectsVector(input.read<std::string>("states"));
    std::string startStateName = input.read<std::string>("start_state");
    for (const auto &string : stateStrings)
    {
        std::shared_ptr<State> newState = std::make_shared<State>(string);
        newState->setMachine(shared_from_this());
        auto transitionStrings = filing::loadObjectsVector(input.read<std::string>("transitions"));
        for (const auto &transitionString : transitionStrings)
        {
            // newState->addTransition() // TODO
        }
        if (newState->name() == startStateName)
        {
            setStartState(newState);
        }
    }

    _currentState = _startState;
}

std::string StateMachine::dump()
{
    if (!_startState)
    {
        throw GameException{"state machine start state has not been recorded, dump can not be handled"};
    }
    filing::JsonIO output = NamedStoredObject::dump();
    output.write<std::string>("start_state", _startState->name());
    std::vector<std::string> statesStrings;
    std::unordered_map<std::string, bool> used;
    _startState->dumpRecursive(statesStrings, used);
    return filing::mergeStrings({output, filing::makeField("states", filing::dumpObjectsVector(statesStrings))});
}

StateMachine::~StateMachine()
{
    if (_currentState)
    {
        _currentState->onStop();
    }
}
} // namespace ample::game
