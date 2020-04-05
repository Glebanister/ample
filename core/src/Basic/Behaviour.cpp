#include <algorithm>

#include "Behaviour.h"
#include "Debug.h"

namespace ample::activity
{
void Behavior::addBehaviour(Behavior &act)
{
    _behaviours.push_back(&act);
}
void Behavior::onAwake()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onAwake(); });
}

void Behavior::onStart()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onStart(); });
}

void Behavior::onActive()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onActive(); });
}

void Behavior::onStop()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onStop(); });
}

void Behavior::onDestroy()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onDestroy(); });
}

void Behavior::onKill()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onKill(); });
}

void Behavior::onPause()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onPause(); });
}
} // namespace ample::activity
