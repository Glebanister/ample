#pragma once

namespace ample::game
{
class NamedObject
{
public:
    NamedObject(const std::string &name = "noname");

    void setClassName(const std::string &className) noexcept;
    std::string &name() noexcept;
    std::string &className() noexcept;

private:
    std::string _name;
    std::string _className = "";
};
} // namespace ample::game
