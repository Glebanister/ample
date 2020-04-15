#include "TimerTransition.h"
#include "Debug.h"

namespace ample::game
{
TimerTransition::TimerTransition(const std::string &name,
                                 std::shared_ptr<StateMachine::State> nextState,
                                 int timeDelta)
    : Transition(name, "TimerTransition", nextState), _timeDelta(timeDelta) {}

void TimerTransition::onStart()
{
    Transition::onStart();
    _startTime = time::Clock::globalTimeMs();
}

bool TimerTransition::listen()
{
    return time::Clock::globalTimeMs() - _startTime > _timeDelta;
}

std::string TimerTransition::dump()
{
    filing::JsonIO output{Transition::dump()};
    output.write<int>("time", _timeDelta);
    return output;
}

} // namespace ample::game
