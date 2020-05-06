#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "Action.h"
#include "Behaviour.h"
#include "EventListener.h"
#include "NamedObject.h"
#include "NamedStoredObject.h"
#include "Namespace.h"
#include "StoredObject.h"

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
        std::string dump() override;
        bool listen() override;

    private:
        std::shared_ptr<State> _nextState;
        bool _activated = false;
    };

    class State : public activity::Behavior, public filing::NamedStoredObject
    {
    public:
        State(StateMachine &machine, const std::string &name, const std::string &className = "State");
        State(const filing::JsonIO &input,
              StateMachine &machine,
              const game::Namespace &globalNamespace);
        State(const filing::JsonIO &input,
              StateMachine &machine);

        void fillActionsNamespace(const game::Namespace &globalNamespace);
        void fillTransitionsNamespace(const game::Namespace &globalNamespace);

        void onStart() override;
        void onActive() override;
        void onStop() override;

        void addTransition(std::shared_ptr<Transition>) noexcept;

        std::string dump() override;
        void dumpRecursive(std::vector<std::string> &strings,
                           std::unordered_map<std::string, bool> &used);

        void addOnStartAction(std::shared_ptr<Action>) noexcept;
        void addOnActiveAction(std::shared_ptr<Action>) noexcept;
        void addOnStopAction(std::shared_ptr<Action>) noexcept;

        std::vector<std::shared_ptr<Action>> &getOnStartActions() noexcept;
        std::vector<std::shared_ptr<Action>> &getOnActiveActions() noexcept;
        std::vector<std::shared_ptr<Action>> &getOnStopActions() noexcept;

        std::vector<std::shared_ptr<Transition>> &transitions() noexcept;

    private:
        StateMachine &_machine;
        std::vector<std::shared_ptr<Transition>> _transitions;
        std::vector<std::shared_ptr<Action>> _onStartActions;
        std::vector<std::shared_ptr<Action>> _onActiveActions;
        std::vector<std::shared_ptr<Action>> _onStopActions;

        friend class StateMachine;
    };

public:
    StateMachine(const std::string &name, const std::string &className = "StateMachine");
    StateMachine(const filing::JsonIO &input, const game::Namespace &globalNamespace);
    void setStartState(std::shared_ptr<State> state);
    void setCurrentState(std::shared_ptr<State> state);
    std::shared_ptr<State> getCurrentState() noexcept;
    void onStart() override;
    void onActive() override;
    void onStop() override;

    std::string dump() override;

    virtual ~StateMachine();

protected:
    std::shared_ptr<State> _startState{nullptr};

private:
    std::shared_ptr<State> _currentState{nullptr};
};
} // namespace ample::game
