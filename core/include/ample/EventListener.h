#pragma once

namespace ample::game::events
{
class EventListener
{
public:
    virtual bool listen() = 0;
    virtual void handleEvent() = 0;
};
} // namespace ample::game::events
