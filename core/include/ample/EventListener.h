#pragma once

#include "Behaviour.h"

namespace ample::game::events
{
class EventListener : public activity::Behavior
{
public:
    virtual bool listen() = 0;
    virtual void handleEvent() = 0;

    void onActive() final;
};
} // namespace ample::game::events
