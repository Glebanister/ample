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
        Transition(State &nextState);
        void handleEvent() final;
        State &getNextState() const noexcept;
        bool isActivated() const noexcept;
        void reset() noexcept;

    private:
        State &_nextState;
        bool _activated = false;
    };

    class State : public activity::Behavior
    {
    public:
        State(StateMachine &machine);
        State();
        void setMachine(StateMachine &machine);

        void onActive() override;
        void addTransition(Transition &) noexcept;

    private:
        StateMachine *_machine;
        std::vector<Transition *> _transitions;
    };

public:
    StateMachine(State &startState);
    void setCurrentState(State &state);
    void onActive() override;

    virtual ~StateMachine();

private:
    State *_currentState;
};
} // namespace ample::game
