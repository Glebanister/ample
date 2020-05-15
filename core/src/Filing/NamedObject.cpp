#include <string>

#include "Exception.h"
#include "NamedObject.h"

namespace ample::filing
{
NamedObject::NamedObject(const std::string &name,
                         const std::string &className,
                         const std::vector<std::string> &knownNames)
    : _name(name),
      _className(className),
      _namespace(std::make_shared<game::Namespace>()),
      _knownNames(knownNames)
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

void NamedObject::fillNamespace(std::shared_ptr<game::Namespace> parentalNamespace,
                                const game::Namespace &globalNamespace)
{
    getNamespace().setParentalNamespace(parentalNamespace);
    for (const auto &name : _knownNames)
    {
        if (!getNamespace().hasName(name))
        {
            throw exception::Exception(exception::exId::UNSPECIFIED,
                                       exception::exType::CASUAL,
                                       "given namespace does not contain name " +
                                           name);
        }
        getNamespace().addObject(globalNamespace.getObject(name));
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
