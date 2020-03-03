#include <cassert>
#include <exception>
#include <algorithm>
#include <iostream>

#include "Activity.h"
#include "EventHandler.h"
#include "EventManager.h"
#include "Exception.h"
#include "Utils.h"

namespace ample::activity
{
void Activity::addActivity(Activity &act)
{
    _subActivities.push_back(&act);
}

void Activity::loop()
{
    std::for_each(_subActivities.begin(), _subActivities.end(),
                  [](auto &x) { x->onAwake(); });
    onAwake();
    _alive = true;
    while (_alive)
    {
        std::for_each(_subActivities.begin(), _subActivities.end(),
                      [](auto &x) { x->onStart(); });
        onStart();
        _running = true;
        while (_running)
        {
            std::for_each(_subActivities.begin(), _subActivities.end(),
                          [](auto &x) { x->onActive(); });
            onActive();
        }
        onStop();
        std::for_each(_subActivities.begin(), _subActivities.end(),
                      [](auto &x) { x->onStop(); });
    }
    onDestroy();
    std::for_each(_subActivities.begin(), _subActivities.end(),
                  [](auto &x) { x->onDestroy(); });
}

void Activity::pause()
{
    std::for_each(_subActivities.begin(), _subActivities.end(),
                  [](auto &x) { x->onPause(); });
    onPause();
    _running = false;
}

void Activity::kill()
{

    std::for_each(_subActivities.begin(), _subActivities.end(),
                  [](auto &x) { x->onKill(); });
    onKill();
    _running = false;
    _alive = false;
}

void Activity::onAwake() {}
void Activity::onStart() {}
void Activity::onActive() {}
void Activity::onStop() {}
void Activity::onDestroy() {}
void Activity::onKill() {}
void Activity::onPause() {}

} // namespace ample::activity
