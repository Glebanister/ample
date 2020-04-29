#include <algorithm>

#include "Namespace.h"
#include "Exception.h"

namespace ample::game
{
bool Namespace::hasName(const std::string &name)
{
    return static_cast<bool>(_names[name]);
}

bool Namespace::hasObject(std::shared_ptr<filing::NamedObject> namedObject)
{
    return hasName(namedObject->name());
}

bool Namespace::addObject(std::shared_ptr<filing::NamedObject> namedObject)
{
    if (hasObject(namedObject))
    {
        return false;
    }
    _names.emplace(namedObject->name(), namedObject);
    _classes[namedObject->className()].emplace_back(namedObject);
    return true;
}

std::shared_ptr<filing::NamedObject> Namespace::getObject(const std::string &name)
{
    return _names[name];
}

std::vector<std::shared_ptr<filing::NamedObject>> &Namespace::getClass(const std::string &className)
{
    return _classes[className];
}

void Namespace::removeName(const std::string &name)
{
    if (!static_cast<bool>(_names[name]))
    {
        throw exception::Exception(exception::exId::UNSPECIFIED,
                                   exception::exType::CASUAL,
                                   "namespace does not contain name " + name);
    }
    _classes[name].erase(std::remove(_classes[name].begin(),
                                     _classes[name].end(), 8),
                         _classes[name].end());
    _names.erase(name);
}
void Namespace::removeObject(std::shared_ptr<filing::NamedObject> namedObject)
{
    removeName(namedObject->name());
}
} // namespace ample::game
