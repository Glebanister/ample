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
    std::cerr << "Loop activity of size" << ' ' << _subActivities.size() << std::endl;
    std::cerr << _subActivities[0] << std::endl;
    assert(_subActivities[0]);
    std::cerr << "Activity.cpp 17" << std::endl;
    std::for_each(_subActivities.begin(), _subActivities.end(),
                  [](auto &x) { x->onAwake(); });
    std::cerr << "Activity.cpp 19" << std::endl;
    onAwake();
    std::cerr << "Activity.cpp 21" << std::endl;
    _alive = true;
    while (_alive)
    {
        std::cerr << "Activity.cpp 25" << std::endl;
        std::for_each(_subActivities.begin(), _subActivities.end(),
                      [](auto &x) { x->onStart(); });
        std::cerr << "Activity.cpp 28" << std::endl;
        onStart();
        std::cerr << "Activity.cpp 30" << std::endl;
        _running = true;
        while (_running)
        {
            std::cerr << "Activity.cpp 34" << std::endl;
            std::for_each(_subActivities.begin(), _subActivities.end(),
                          [](auto &x) { x->onActive(); });
            std::cerr << "Activity.cpp 37" << std::endl;
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
