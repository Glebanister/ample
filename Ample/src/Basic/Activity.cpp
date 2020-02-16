#include <cassert>
#include <exception>

#include "Activity.h"
#include "EventHandler.h"
#include "EventManager.h"
#include "Error.h"
#include "Utils.h"

namespace activity
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
        _alive = false;
    }
}

void onAwake() {}
void onStart() {}
void onActive() {}
void onStop() {}
void onDestroy() {}

bool onKill() { return true; }
bool onPause() { return true; }

bool _alive = false;
bool _running = false;
} // namespace activity
