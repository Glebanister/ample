#pragma once

namespace ample::gui
{
template <class T>
TabObjectBrowser<T>::TabObjectBrowser(std::shared_ptr<T> object)
    : _browserTarget(object) {}

template <class T>
std::shared_ptr<T> TabObjectBrowser<T>::browserTarget() const noexcept
{
    return _browserTarget;
}

template <class T>
std::shared_ptr<filing::NamedObject> TabObjectBrowser<T>::browserTargetNamedObject() const noexcept
{
    return _browserTarget;
}
} // namespace ample::gui
