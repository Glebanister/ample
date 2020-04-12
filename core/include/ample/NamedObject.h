#pragma once

namespace ample::game
{
class NamedObject
{
public:
    NamedObject(const std::string &className, const std::string &name);

    std::string &name() noexcept;
    std::string &className() noexcept;

private:
    std::string _name;
    std::string _className = "";
};
} // namespace ample::game
