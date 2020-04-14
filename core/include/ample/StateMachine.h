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
class StateMachine : public activity::Behavior, public filing::NamedStoredObject, public std::enable_shared_from_this<StateMachine>
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
        std::string dump() override;

    private:
        std::shared_ptr<State> _nextState;
        bool _activated = false;
    };

    class State : public activity::Behavior, public filing::NamedStoredObject
    {
    public:
        State(std::shared_ptr<StateMachine> machine, const std::string &name);
        State(const std::string &name);

        void setMachine(std::shared_ptr<StateMachine> machine) noexcept;

        void onStart() override;
        void onActive() override;
        void onStop() override;

        void addTransition(std::shared_ptr<Transition>) noexcept;

        // TODO : apply function using dfs
        void dumpRecursive(std::vector<std::string> &strings,
                           std::unordered_map<std::string, bool> &used);

        State(const filing::JsonIO &input);

        void addOnStartAction(std::shared_ptr<Action>) noexcept;
        void addOnActiveAction(std::shared_ptr<Action>) noexcept;
        void addOnStopAction(std::shared_ptr<Action>) noexcept;

    private:
        std::string dump() override;
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

    StateMachine(const filing::JsonIO &input);
    std::string dump() override;

    virtual ~StateMachine();

private:
    std::shared_ptr<State> _currentState{nullptr};
    std::shared_ptr<State> _startState{nullptr};
};
} // namespace ample::game
