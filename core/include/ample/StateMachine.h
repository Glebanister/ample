#pragma once

#include <vector>
#include <memory>

#include "Behaviour.h"
#include "EventListener.h"

namespace ample::game
{
class StateMachine : public activity::Behavior
{
public:
    class State;

    class Transition : public events::EventListener
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

    class State : public activity::Behavior
    {
    public:
        State(std::shared_ptr<StateMachine> machine, const std::string &name = "state_name");
        State(const std::string &name = "state_name");

        void setMachine(std::shared_ptr<StateMachine> machine) noexcept;

        void onActive() override;
        void addTransition(std::shared_ptr<Transition>) noexcept;

        std::string getName() const noexcept;

    private:
        std::shared_ptr<StateMachine> _machine;
        std::vector<std::shared_ptr<Transition>> _transitions;
        std::string _name;

        friend class StateMachine;
    };

public:
    StateMachine() = default;
    void setStartState(std::shared_ptr<State> state);
    void setCurrentState(std::shared_ptr<State> state);
    void onActive() override;

    virtual ~StateMachine();

private:
    std::shared_ptr<State> _currentState{nullptr};
};
} // namespace ample::game
