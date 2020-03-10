#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "EventManager.h"
#include "EventHandler.h"
#include "Clock.h"
#include "Debug.h"
#include "Behaviour.h"

namespace ample::activity
{
class Activity : public Behaviour
{
public:
    void loop();
    void pause();
    void kill();

protected:
    bool _alive = false;
    bool _running = false;
};
} // namespace ample::activity
