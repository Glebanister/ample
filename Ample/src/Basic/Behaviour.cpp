#include "Behaviour.h"

namespace ample::activity
{
void Behaviour::addBehaviour(Behaviour &act)
{
    _behaviours.push_back(&act);
}
void Behaviour::onAwake() {}
void Behaviour::onStart() {}
void Behaviour::onActive() {}
void Behaviour::onStop() {}
void Behaviour::onDestroy() {}
} // namespace ample::activity
