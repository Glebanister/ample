#include "TimerTransition.h"
#include "Debug.h"

namespace ample::game
{
TimerTransition::TimerTransition(std::shared_ptr<StateMachine::State> nextState, int timeDelta)
    : Transition(nextState), _timeDelta(timeDelta) {}

void TimerTransition::onStart()
{
    Transition::onStart();
    _startTime = time::Clock::globalTimeMs();
    DEBUG("ON START!");
}

bool TimerTransition::listen()
{
    return time::Clock::globalTimeMs() - _startTime > _timeDelta;
}

} // namespace ample::game
