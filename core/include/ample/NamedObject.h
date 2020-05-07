#pragma once

#include <memory>
#include <string>

#include "Namespace.h"
#include "JsonIO.h"

namespace ample::game
{
class Namespace;
} // namespace ample::game

namespace ample::filing
{
class NamedObject
{
public:
    NamedObject(const std::string &name,
                const std::string &className,
                const std::vector<std::string> &knownNames = {});

    void fillNamespace(const game::Namespace &globalNamespace);

    std::string name() const noexcept;
    std::string className() const noexcept;

    game::Namespace &getNamespace() noexcept;

    virtual ~NamedObject() = default;

protected:
    std::string _name;
    std::string _className;
    std::shared_ptr<game::Namespace> _namespace;
    std::vector<std::string> _knownNames;
};
} // namespace ample::filing
