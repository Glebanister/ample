#pragma once

#include <memory>
#include <string>

#include "JsonIO.h"
#include "Namespace.h"

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
                const std::string &className);

    void setNamespace(std::shared_ptr<game::Namespace>);

    std::string name() const noexcept;
    std::string className() const noexcept;

    game::Namespace &getNamespace() noexcept;
    std::shared_ptr<game::Namespace> getNamespacePointer() noexcept;

    virtual ~NamedObject() = default;

protected:
    std::string _name;
    std::string _className;
    std::shared_ptr<game::Namespace> _namespace;
};
} // namespace ample::filing
