#pragma once

#include <memory>
#include <unordered_map>
#include <functional>

namespace ample::utits
{
template <typename T>
class Factory
{
public:
    typedef std::unordered_map<std::string, std::function<std::unique_ptr<T>()>> registryMap;

    static std::unique_ptr<T> produce(const std::string &name)
    {
        auto it = ShapeFactory::registry().find(name);
        return it == ShapeFactory::registry().end() ? nullptr : (it->second)();
    }

    static registryMap &registry()
    {
        static registryMap impl;
        return impl;
    }

public:
    template <typename Derived, typename... Args>
    struct Register
    {
        Register(std::string name, Args... args)
        {
            Factory::registry()[name] = []() { return std::make_unique<Derived>(args); };
        }
    };
};
} // namespace ample::utits

#include <templates/Factory.hpp>
