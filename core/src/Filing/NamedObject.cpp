#include <string>

#include "Exception.h"
#include "NamedObject.h"

namespace ample::filing
{
NamedObject::NamedObject(const std::string &name,
                         const std::string &className)
    : _name(name),
      _className(className),
      _namespace(std::make_shared<game::Namespace>())
{
    if (name.empty())
    {
        throw exception::Exception{exception::exId::UNSPECIFIED, exception::exType::CASUAL,
                                   "object name can not empty"};
    }
    if (className.empty())
    {
        throw exception::Exception{exception::exId::UNSPECIFIED, exception::exType::CASUAL,
                                   "object class name can not empty"};
    }
}

void NamedObject::setNamespace(std::shared_ptr<game::Namespace> names)
{
    _namespace = names;
}

std::string NamedObject::name() const noexcept
{
    return _name;
}

game::Namespace &NamedObject::getNamespace() noexcept
{
    return *_namespace;
}

std::shared_ptr<game::Namespace> NamedObject::getNamespacePointer() noexcept
{
    return _namespace;
}

std::string NamedObject::className() const noexcept
{
    return _className;
}
} // namespace ample::filing
