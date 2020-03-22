#include <cassert>
#include <exception>
#include <algorithm>
#include <iostream>

#include "Activity.h"
#include "EventHandler.h"
#include "EventManager.h"
#include "Exception.h"
#include "Utils.h"
#include "Debug.h"

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
    onPause();
    _running = false;
}

void Activity::kill()
{
    onKill();
    _running = false;
    _alive = false;
}
} // namespace ample::activity
