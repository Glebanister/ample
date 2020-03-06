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
void Activity::loop()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onAwake(); });
    onAwake();
    _alive = true;
    while (_alive)
    {
        std::for_each(_behaviours.begin(), _behaviours.end(),
                      [](auto &x) { x->onStart(); });
        onStart();
        _running = true;
        while (_running)
        {
            std::for_each(_behaviours.begin(), _behaviours.end(),
                          [](auto &x) { x->onActive(); });
            onActive();
        }
        onStop();
        std::for_each(_behaviours.begin(), _behaviours.end(),
                      [](auto &x) { x->onStop(); });
    }
    onDestroy();
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onDestroy(); });
}

void Activity::pause()
{
    for (auto & beh : _behaviours)
    {
        beh->onPause();
    }
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onPause(); });
    onPause();
    _running = false;
}

void Activity::kill()
{

    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onKill(); });
    onKill();
    _running = false;
    _alive = false;
}
} // namespace ample::activity
