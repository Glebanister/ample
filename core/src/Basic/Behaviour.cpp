#include <algorithm>

#include "Behaviour.h"
#include "Debug.h"

namespace ample::activity
{
void Behavior::addBehavior(std::shared_ptr<Behavior> beh)
{
    _behaviours.push_back(beh);
}

void Behavior::removeBehavior(std::shared_ptr<Behavior> beh)
{
    std::remove(_behaviours.begin(), _behaviours.end(), beh);
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
