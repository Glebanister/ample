#include <string>

#include "NamedObject.h"

namespace ample::game
{
NamedObject::NamedObject(const std::string &name)
    : _name(name) {}

std::string &NamedObject::name() noexcept
{
    return _name;
}
} // namespace ample::game
