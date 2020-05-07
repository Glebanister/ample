#pragma once

namespace ample::utils
{
template <class Base, typename... Args>
std::unique_ptr<Base> Factory<Base, Args...>::produce(const std::string &className, Args... args)
{
    return std::move(std::unique_ptr<Base>(registry().at(className)(std::forward<Args>(args)...)));
}

template <class Base, typename... Args>
typename Factory<Base, Args...>::registryMap &Factory<Base, Args...>::registry()
{
    static registryMap impl;
    return impl;
}

template <class Base, typename... Args>
template <class Derived>
Factory<Base, Args...>::Register<Derived>::Register(const std::string &className)
{
    Factory::registry()[className] = [=](Args... args) { return std::make_unique<Derived>(args...); };
}
} // namespace ample::utils
