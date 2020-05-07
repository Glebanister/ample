#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace ample::utils
{
template <class Base, typename... Args>
class Factory
{
public:
    using registerFucntion = std::function<std::unique_ptr<Base>(Args...)>;
    using registryMap = std::unordered_map<std::string, registerFucntion>;

    static std::unique_ptr<Base> produce(const std::string &className, Args... args);
    static registryMap &registry();

public:
    template <class Derived>
    struct Register
    {
        Register(const std::string &className);
    };
};
} // namespace ample::utils

#include <templates/Factory.hpp>
