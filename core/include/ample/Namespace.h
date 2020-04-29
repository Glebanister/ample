#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "NamedObject.h"

namespace ample::game
{
class Namespace
{
public:
    bool hasName(const std::string &name);
    bool hasObject(std::shared_ptr<filing::NamedObject> namedObject);

    bool addObject(std::shared_ptr<filing::NamedObject> namedObject);

    std::shared_ptr<filing::NamedObject> getObject(const std::string &name);
    std::vector<std::shared_ptr<filing::NamedObject>> &getClass(const std::string &className);

    void removeName(const std::string &name);
    void removeObject(std::shared_ptr<filing::NamedObject> namedObject);

private:
    std::unordered_map<std::string, std::shared_ptr<filing::NamedObject>> _names;
    std::unordered_map<std::string, std::vector<std::shared_ptr<filing::NamedObject>>> _classes;
};
} // namespace ample::game
