#pragma once

namespace ample::utils
{
template <class Base>
std::unique_ptr<Base> Factory<Base>::produce(const std::string &className, const std::string &data)
{
    auto it = Factory<Base>::registry().find(className);
    return it == Factory<Base>::registry().end() ? nullptr : (it->second)(data);
}

template <class Base>
typename Factory<Base>::registryMap &Factory<Base>::registry()
{
    static registryMap impl;
    return impl;
}

template <class Base>
template <class Derived>
Factory<Base>::Register<Derived>::Register(std::string className)
{
    Factory::registry()[className] = [=](const std::string &data) { return std::make_unique<Derived>(data); };
}
} // namespace ample::utils
