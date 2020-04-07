#include <string>

#include "NamedObject.h"
#include "GameException.h"

namespace ample::game
{
NamedObject::NamedObject(const std::string &name)
    : _name(name)
{
    if (name.length() == 0)
    {
        throw GameException{"object name can not empty"};
    }
}

void NamedObject::setClassName(const std::string &className) noexcept
{
    _className = className;
}

std::string &NamedObject::name() noexcept
{
    return _name;
}
} // namespace ample::game
