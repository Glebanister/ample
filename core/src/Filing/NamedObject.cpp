#include <string>

#include "NamedObject.h"
#include "Exception.h"

namespace ample::filing
{
NamedObject::NamedObject(const std::string &name, const std::string &className)
    : _name(name), _className(className)
{
    if (name.length() == 0)
    {
        throw exception::Exception{exception::exId::UNSPECIFIED,
                                   exception::exType::CASUAL,
                                   "object name can not empty"};
    }
    if (className.length() == 0)
    {
        throw exception::Exception{exception::exId::UNSPECIFIED,
                                   exception::exType::CASUAL,
                                   "object class name can not empty"};
    }
}

std::string NamedObject::name() const noexcept
{
    return _name;
}

std::string NamedObject::className() const noexcept
{
    return _className;
}
} // namespace ample::filing
