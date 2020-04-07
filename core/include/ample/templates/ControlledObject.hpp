#pragma once

// #include "GameException.h"
// #include "Debug.h"
// #include "ample/Debug.h"
// #include "ample/GameException.h"

namespace ample::game
{
template <class ObjectT>
ControlledObject::ObjectState<ObjectT>::ObjectState(const std::string &name, std::shared_ptr<ObjectT> object)
    : State(name), _object(object)
{
    setMachine(object->stateMachine());
}

template <class ObjectT>
std::shared_ptr<ObjectT> ControlledObject::ObjectState<ObjectT>::object() const noexcept
{
    return _object;
}
} // namespace ample::game
