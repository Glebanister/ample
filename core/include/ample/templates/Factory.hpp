#pragma once

namespace ample::utils
{
template <typename T>
static std::unique_ptr<T> Factory<T>::produce(const std::string &name)
{
    auto it = ShapeFactory::registry().find(name);
    return it == ShapeFactory::registry().end() ? nullptr : (it->second)();
}

template <typename T>
static Factory<T>::registryMap &Factory<T>::registry()
{
    static registryMap impl;
    return impl;
}

template <typename T, typename Derived, typename... Args>
Factory<T>::Register<Derived, Args>::Register(std::string name, Args... args)
{
    Factory<T>::registry()[name] = []() { return std::make_unique<Derived>(args); };
}
} // namespace ample::utils
