#pragma once

#include <string>

namespace ample::filing
{
class NamedObject
{
public:
    NamedObject(const std::string &name, const std::string &className);

    std::string name() const noexcept;
    std::string className() const noexcept;

private:
    std::string _name;
    std::string _className;
};
} // namespace ample::game
