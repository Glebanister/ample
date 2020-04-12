#include <string>

#include "NamedObject.h"
#include "GameException.h"

namespace ample::game
{
NamedObject::NamedObject(const std::string &className, const std::string &name)
    : _name(name), _className(className)
{
    if (name.length() == 0)
    {
        throw GameException{"object name can not empty"};
    }
    if (className.length() == 0)
    {
        throw GameException{"object class name can not empty"};
    }
}

std::string &NamedObject::name() noexcept
{
    return _name;
}

std::string &NamedObject::className() noexcept
{
    return _className;
}
} // namespace ample::game
