#include <algorithm>

#include "Behaviour.h"
#include "Debug.h"

namespace ample::activity
{
void Behaviour::addBehaviour(Behaviour &act)
{
    _behaviours.push_back(&act);
}
void Behaviour::onAwake()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onAwake(); });
}

void Behaviour::onStart()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onStart(); });
}

void Behaviour::onActive()
{
    DEBUG("Behaviour is active");
    DEBUG(typeid(*this).name());
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onActive(); });
    DEBUG("Behaviour is activated");
}

void Behaviour::onStop()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onStop(); });
}

void Behaviour::onDestroy()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onDestroy(); });
}

void Behaviour::onKill()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onKill(); });
}

void Behaviour::onPause()
{
    std::for_each(_behaviours.begin(), _behaviours.end(),
                  [](auto &x) { x->onPause(); });
}
} // namespace ample::activity
