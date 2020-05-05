#pragma once

namespace ample::gui
{
template <class T>
TabObjectEditor<T>::TabObjectEditor(std::shared_ptr<T> object)
    : _editorTarget(object) {}

template <class T>
std::shared_ptr<T> TabObjectEditor<T>::editorTarget() const noexcept
{
    return _editorTarget;
}

template <class T>
std::shared_ptr<filing::NamedObject> TabObjectEditor<T>::editorTargetNamedObject() const noexcept
{
    return _editorTarget;
}
} // namespace ample::gui
