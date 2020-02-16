#pragma once

#include <vector>

#include "EventManager.h"
#include "EventHandler.h"
#include "Clock.h"

namespace ample::activity
{
class Activity
{
public:
    void loop();
    void pause();
    void kill();

    virtual ~Activity() = default;

protected:
    virtual void onAwake();
    virtual void onStart();
    virtual void onActive();
    virtual void onStop();
    virtual void onDestroy();

    virtual bool onKill();
    virtual bool onPause();

    bool _alive = false;
    bool _running = false;
};
} // namespace ample::activity
