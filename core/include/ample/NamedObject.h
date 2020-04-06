#pragma once

namespace ample::game
{
class NamedObject
{
public:
    NamedObject(const std::string &name = "noname");
    std::string &name() noexcept;

private:
    std::string _name;
};
} // namespace ample::game
