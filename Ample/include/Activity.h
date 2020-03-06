#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "EventManager.h"
#include "EventHandler.h"
#include "Clock.h"
#include "Debug.h"

namespace ample::activity
{
class Activity
{
public:
    void loop();
    void pause();
    void kill();

    void addBehaviour(Activity &act);

    virtual ~Activity() = default;

protected:
    virtual void onAwake();
    virtual void onStart();
    virtual void onActive();
    virtual void onStop();
    virtual void onDestroy();

    virtual void onKill();
    virtual void onPause();

    bool _alive = false;
    bool _running = false;

    std::vector<Activity *> _behaviours;
};
} // namespace ample::activity
