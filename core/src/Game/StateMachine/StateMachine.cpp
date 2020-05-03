#include <iostream>
#include <memory>
#include <numeric>

#include "ActionsFactory.h"
#include "Debug.h"
#include "Factory.h"
#include "GameException.h"
#include "StateFactory.h"
#include "StateMachine.h"
#include "TransitionsFactory.h"

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

StateMachine::State::State(StateMachine &machine, const std::string &name, const std::string &className)
    : NamedStoredObject(name, className), _machine(machine) {}

void StateMachine::State::addTransition(std::shared_ptr<StateMachine::Transition> transition) noexcept
{
    addBehavior(std::static_pointer_cast<Behavior>(transition));
    _transitions.push_back(transition);
}

std::vector<std::shared_ptr<StateMachine::Transition>> &StateMachine::State::transitions() noexcept
{
    return _transitions;
}

void StateMachine::State::onStart()
{
    activity::Behavior::onStart();
    for (const auto &action : _onStartActions)
    {
        action->onActive();
    }
}

void StateMachine::State::onStop()
{
    activity::Behavior::onStop();
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
            throw GameException{"empty transition"};
        }
        // transition->onActive();
        if (transition->isActivated())
        {
            transition->reset();
            _machine.setCurrentState(transition->getNextState());
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

StateMachine::State::State(const filing::JsonIO &input,
                           StateMachine &machine,
                           const game::Namespace &globalNamespace)
    : NamedStoredObject(input), _machine(machine)
{
    auto onStartActionStrings = filing::loadObjectsVector(input.updateJsonIO("on_start"));
    auto onActiveActionStrings = filing::loadObjectsVector(input.updateJsonIO("on_active"));
    auto onStopActionStrings = filing::loadObjectsVector(input.updateJsonIO("on_stop"));
    for (const auto &actionString : onStartActionStrings)
    {
        addOnStartAction(factory::ActionsFactory.produce(filing::JsonIO(actionString).read<std::string>("class_name"),
                                                         actionString));
        _onStartActions.back()->fillNamespace(_namespace, globalNamespace);
    }
    for (const auto &actionString : onActiveActionStrings)
    {
        addOnActiveAction(factory::ActionsFactory.produce(filing::JsonIO(actionString).read<std::string>("class_name"),
                                                          actionString));
        _onActiveActions.back()->fillNamespace(_namespace, globalNamespace);
    }
    for (const auto &actionString : onStopActionStrings)
    {
        addOnStopAction(factory::ActionsFactory.produce(filing::JsonIO(actionString).read<std::string>("class_name"),
                                                        actionString));
        _onStopActions.back()->fillNamespace(_namespace, globalNamespace);
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
    // TODO: use iterators?
    for (const auto &act : _onStartActions)
    {
        startActions.emplace_back(act->dump());
    }
    for (const auto &act : _onActiveActions)
    {
        activeActions.emplace_back(act->dump());
    }
    for (const auto &act : _onStopActions)
    {
        stopActions.emplace_back(act->dump());
    }
    return filing::mergeStrings({
        output.getJSONstring(),
        filing::makeField("on_active", filing::dumpObjectsVector(activeActions)),
        filing::makeField("on_start", filing::dumpObjectsVector(startActions)),
        filing::makeField("on_stop", filing::dumpObjectsVector(stopActions)),
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

StateMachine::StateMachine(const std::string &name, const std::string &className)
    : NamedStoredObject(name, className) {}

StateMachine::StateMachine(const filing::JsonIO &input,
                           const game::Namespace &globalNamespace) // TODO: implement immediate mode states loading
    : NamedStoredObject(input)
{
    auto stateStrings = filing::loadObjectsVector(input.updateJsonIO("states"));
    std::string startStateName = input.read<std::string>("start_state");
    std::unordered_map<std::string, std::shared_ptr<State>> statesMap;
    for (const filing::JsonIO &string : stateStrings)
    {
        std::shared_ptr<State> newState = factory::StateFactory.produce(string.read<std::string>("class_name"),
                                                                        string,
                                                                        *this,
                                                                        globalNamespace);
        newState->fillNamespace(_namespace, globalNamespace);
        if (newState->name() == startStateName)
        {
            setStartState(newState);
        }
        statesMap[newState->name()] = newState;
    }
    for (const filing::JsonIO &stateData : stateStrings)
    {
        auto transitionStrings = filing::loadObjectsVector(stateData.updateJsonIO("transitions"));
        auto currentState = statesMap[stateData.read<std::string>("name")];
        for (const filing::JsonIO &transitionData : transitionStrings)
        {
            std::string transitionClass = transitionData.read<std::string>("class_name");
            auto nextState = statesMap[transitionData.read<std::string>("to")];
            currentState->addTransition(
                game::factory::TransitionsFactory.produce(
                    transitionClass,
                    transitionData.getJSONstring(),
                    nextState));
            currentState->_transitions.back()->fillNamespace(currentState->_namespace, globalNamespace);
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
