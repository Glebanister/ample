#include "CollisionTransition.h"
#include "GameException.h"
#include "WorldContact2d.h"
#include "WorldObject2d.h"
#include <algorithm>

namespace ample::game::stateMachine::transitions
{
CollisionTransition::CollisionTransition(const std::string &name,
                                         std::shared_ptr<StateMachine::State> nextState,
                                         const std::vector<std::string> &bodyNames,
                                         size_t triggerStartIdx)
    : PhysicalTransition(name,
                         "CollisionTransition",
                         nextState,
                         bodyNames),
      _triggerStartIdx(triggerStartIdx)
{
    if (bodyNames.empty() || _triggerStartIdx == 0)
    {
        throw GameException("There isn't no trigger object");
    }
    if (bodyNames.size() < 2 || _triggerStartIdx >= bodyNames.size())
    {
        throw GameException("At least one trigger must be specified");
    }

    std::copy(_bodyNames.begin() + _triggerStartIdx, _bodyNames.end(),
              std::inserter(_triggers, _triggers.end()));
}

CollisionTransition::CollisionTransition(const filing::JsonIO &input,
                                         std::shared_ptr<StateMachine::State> nextState)
    : PhysicalTransition(input, nextState),
      _triggerStartIdx(input.read<size_t>("trigger_start_idx"))
{
    std::copy(_bodyNames.begin() + _triggerStartIdx, _bodyNames.end(),
              std::inserter(_triggers, _triggers.end()));
}

std::string CollisionTransition::dump()
{
    filing::JsonIO result = PhysicalTransition::dump();
    result.write<size_t>("trigger_start_idx", _triggerStartIdx);
    return result;
}

bool CollisionTransition::listen()
{
    ASSERT(_pointersInitialized);

    for (size_t i = 0; i < _triggerStartIdx; ++i)
    {
        auto currentContact = _bodyPointers[i]->getContactList();
        while (currentContact)
        {
            if (_triggers.find(currentContact.getOther().name()) != _triggers.end())
            {
                return true;
            }

            currentContact = currentContact.getNext();
        }
    }

    return false;
}
} // namespace ample::game::stateMachine::transitions