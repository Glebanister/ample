#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "NamedObject.h"

namespace ample::filing
{
class NamedObject;
}

namespace ample::game
{
class Namespace
{
public:
    Namespace(std::shared_ptr<Namespace> parent);

    bool hasName(const std::string &name);
    bool hasObject(std::shared_ptr<filing::NamedObject> namedObject);

    bool addObject(std::shared_ptr<filing::NamedObject> namedObject);

    std::shared_ptr<filing::NamedObject> getObject(const std::string &name) const;
    std::unordered_map<std::string, std::shared_ptr<filing::NamedObject>> &getAllNames() noexcept;

    void removeName(const std::string &name);
    void removeObject(std::shared_ptr<filing::NamedObject> namedObject);

private:
    mutable std::unordered_map<std::string, std::shared_ptr<filing::NamedObject>> _names;
    
    std::shared_ptr<Namespace> _parentalNamespace;
};
} // namespace ample::game
