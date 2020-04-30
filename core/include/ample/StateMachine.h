#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "Behaviour.h"
#include "EventListener.h"
#include "NamedObject.h"
#include "StoredObject.h"
#include "Action.h"
#include "NamedStoredObject.h"

namespace ample::game
{
class StateMachine : public activity::Behavior, public filing::NamedStoredObject
{
public:
    class State;

    class Transition : public events::EventListener, public filing::NamedStoredObject
    {
    public:
        Transition(const std::string &name,
                   const std::string &className,
                   std::shared_ptr<State> nextState);
        void handleEvent() final;
        std::shared_ptr<State> getNextState() const noexcept;
        bool isActivated() const noexcept;
        void reset() noexcept;
        filing::JsonIO dump() override;

    private:
        std::shared_ptr<State> _nextState;
        bool _activated = false;
    };

    class State : public activity::Behavior, public filing::NamedStoredObject
    {
    public:
        State(StateMachine &machine, const std::string &name);
        State(const filing::JsonIO &input, StateMachine &machine);

        void onStart() override;
        void onActive() override;
        void onStop() override;

        void addTransition(std::shared_ptr<Transition>) noexcept;

        void dumpRecursive(std::vector<std::string> &strings,
                           std::unordered_map<std::string, bool> &used);


        void addOnStartAction(std::shared_ptr<Action>) noexcept;
        void addOnActiveAction(std::shared_ptr<Action>) noexcept;
        void addOnStopAction(std::shared_ptr<Action>) noexcept;

    private:
        filing::JsonIO dump() override;
        StateMachine &_machine;
        std::vector<std::shared_ptr<Transition>> _transitions;
        std::vector<std::shared_ptr<Action>> _onStartActions;
        std::vector<std::shared_ptr<Action>> _onActiveActions;
        std::vector<std::shared_ptr<Action>> _onStopActions;

        friend class StateMachine;
    };

public:
    StateMachine(const std::string &name);
    void setStartState(std::shared_ptr<State> state);
    void setCurrentState(std::shared_ptr<State> state);
    std::shared_ptr<State> getCurrentState() noexcept;
    void onActive() override;

    StateMachine(const filing::JsonIO &input);
    filing::JsonIO dump() override;

    virtual ~StateMachine();

private:
    std::shared_ptr<State> _currentState{nullptr};
    std::shared_ptr<State> _startState{nullptr};
};
} // namespace ample::game
