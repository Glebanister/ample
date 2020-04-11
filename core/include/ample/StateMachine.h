#pragma once

#include <vector>
#include <memory>

#include "Behaviour.h"
#include "EventListener.h"
#include "NamedObject.h"
#include "StoredObject.h"
#include "Action.h"

namespace ample::game
{
class StateMachine : public activity::Behavior, public filing::StoredObject, public NamedObject
{
public:
    class State;

    class Transition : public events::EventListener, public filing::StoredObject
    {
    public:
        Transition(std::shared_ptr<State> nextState);
        void handleEvent() final;
        std::shared_ptr<State> getNextState() const noexcept;
        bool isActivated() const noexcept;
        void reset() noexcept;

    private:
        std::shared_ptr<State> _nextState;
        bool _activated = false;
    };

    class State : public activity::Behavior, public NamedObject, public filing::StoredObject
    {
    public:
        State(std::shared_ptr<StateMachine> machine, const std::string &name);
        State(const std::string &name);

        void setMachine(std::shared_ptr<StateMachine> machine) noexcept;

        void onStart() override;
        void onActive() override;
        void onStop() override;

        void addOnStartAction(std::shared_ptr<Action>);
        void addOnActiveAction(std::shared_ptr<Action>);
        void addOnStopAction(std::shared_ptr<Action>);

        void addTransition(std::shared_ptr<Transition>) noexcept;

        // TODO : apply function using dfs
        void dumpTransitions(std::vector<std::string> &strings, filing::JsonIO);

    private:
        std::shared_ptr<StateMachine> _machine;
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

    std::string dump(filing::JsonIO input, const std::string &) override;

    virtual ~StateMachine();

private:
    std::shared_ptr<State> _currentState{nullptr};
    std::shared_ptr<State> _startState{nullptr};
};
} // namespace ample::game
