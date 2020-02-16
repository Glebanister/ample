#include <cassert>
#include <exception>

#include "Activity.h"
#include "EventHandler.h"
#include "EventManager.h"
#include "Exception.h"
#include "Utils.h"

namespace ample::activity
{
void Activity::loop()
{
    onAwake();
    _alive = true;
    while (_alive)
    {
        onStart();
        _running = true;
        while (_running)
        {
            onActive();
        }
        onStop();
    }
    onDestroy();
}

void Activity::pause()
{
    if (onPause())
    {
        _running = false;
    }
}

void Activity::kill()
{
    if (onKill())
    {
        _running = false;
        _alive = false;
    }
}

void Activity::onAwake() {}
void Activity::onStart() {}
void Activity::onActive() {}
void Activity::onStop() {}
void Activity::onDestroy() {}

bool Activity::onKill() { return true; }
bool Activity::onPause() { return true; }

bool _alive = false;
bool _running = false;
} // namespace ample::activity
