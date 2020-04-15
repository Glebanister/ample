#pragma once

#include "StateMachine.h"
#include "Clock.h"

namespace ample::game
{
class TimerTransition : public StateMachine::Transition
{
public:
    TimerTransition(const std::string &name,
                    std::shared_ptr<StateMachine::State> nextState,
                    int timeDelta);
    // TimerTransition(std::shared_ptr<StateMachine::State> nextState, int timeDelta);
    std::string dump() override;

    void onStart() override;
    bool listen() override;

private:
    const int _timeDelta;
    int _startTime;
};
} // namespace ample::game
