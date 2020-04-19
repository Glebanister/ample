#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

namespace ample::utils
{
template <class Base>
class Factory
{
public:
    using registryMap = std::unordered_map<std::string, std::function<std::unique_ptr<Base>(std::string)>>;

    static std::unique_ptr<Base> produce(const std::string &className, const std::string &objectData);
    static registryMap &registry();

public:
    template <class Derived>
    struct Register
    {
        Register(std::string className);
    };
};
} // namespace ample::utils

#include <templates/Factory.hpp>
