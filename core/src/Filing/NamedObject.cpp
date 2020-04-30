#include <string>

#include "Exception.h"
#include "NamedObject.h"

namespace ample::filing
{
NamedObject::NamedObject(const std::string &name,
                         const std::string &className,
                         std::shared_ptr<game::Namespace> parentalNamespace)
    : _name(name),
      _className(className),
      _namespace(std::make_shared<game::Namespace>(parentalNamespace))
{
    if (name.length() == 0)
    {
        throw exception::Exception{exception::exId::UNSPECIFIED, exception::exType::CASUAL,
                                   "object name can not empty"};
    }
    if (className.length() == 0)
    {
        throw exception::Exception{exception::exId::UNSPECIFIED, exception::exType::CASUAL,
                                   "object class name can not empty"};
    }
}

std::string NamedObject::name() const noexcept
{
    return _name;
}

game::Namespace &NamedObject::getNamespace() noexcept
{
    return *_namespace;
}

std::string NamedObject::className() const noexcept
{
    return _className;
}
} // namespace ample::filing
