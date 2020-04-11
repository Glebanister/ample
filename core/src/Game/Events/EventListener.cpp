#include "EventListener.h"

namespace ample::game::events
{
void EventListener::onActive()
{
    activity::Behavior::onActive();
    if (listen())
    {
        handleEvent();
    }
}
} // namespace ample::game::event
