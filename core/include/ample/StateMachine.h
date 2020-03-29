#pragma once

#include <vector>
#include <memory>

#include "Behaviour.h"
#include "EventListener.h"

namespace ample::game
{
class StateMachine : public activity::Behaviour
{
public:
    class State;

    class Trigger : public events::EventListener
    {
    public:
        Trigger(const StateMachine &machine);
        void handleEvent() override;
    };

    template <class EventListenerT, typename... Args>
    class TransitionAbstract
    {
    public:
        Transition(State &nextState, Args... eventListenerArgs);

    private:
        EventListenerT _listener;
    };

    class State : public activity::Behaviour
    {
    public:
    private:
        // std::vector<std::pair<std::shared_ptr<State>> _connections;
    };

public:
private:
};
} // namespace ample::game
