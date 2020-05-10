#include <algorithm>

#include "Exception.h"
#include "Namespace.h"

namespace ample::game
{
void Namespace::setParentalNamespace(std::shared_ptr<Namespace> parent)
{
    _parentalNamespace = std::move(parent);
}

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
    return true;
}

std::shared_ptr<filing::NamedObject> Namespace::getObject(const std::string &name) const
{
    const Namespace *currentNamespace = this;
    while (currentNamespace && !currentNamespace->_names.find(name)->second)
    {
        currentNamespace = currentNamespace->_parentalNamespace.get();
    }
    if (!currentNamespace)
    {
        return nullptr;
    }
    return currentNamespace->_names.find(name)->second;
}

std::unordered_map<std::string, std::shared_ptr<filing::NamedObject>> &Namespace::getAllNames() noexcept
{
    return _names;
}

void Namespace::removeName(const std::string &name)
{
    if (!static_cast<bool>(_names[name]))
    {
        throw exception::Exception(exception::exId::UNSPECIFIED, exception::exType::CASUAL,
                                   "namespace does not contain name " + name);
    }
    _names.erase(name);
}
void Namespace::removeObject(std::shared_ptr<filing::NamedObject> namedObject)
{
    removeName(namedObject->name());
}

void Namespace::clear() noexcept
{
    _names.clear();
    _parentalNamespace.reset();
}
} // namespace ample::game
