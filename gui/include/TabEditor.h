#pragma once

#include <memory>

#include "ample/NamedObject.h"

#include "InterfaceUnit.h"

namespace ample::gui
{
class TabEditor : public GraphicalInterface
{
public:
    virtual std::shared_ptr<filing::NamedObject> editorTargetNamedObject() const noexcept = 0;
    void setActive(bool flag) { _isActive = flag; }
    bool isActive() const noexcept { return _isActive; }

private:
    bool _isActive;
};

template <class T>
class TabObjectEditor : public TabEditor
{
public:
    TabObjectEditor(std::shared_ptr<T>);
    std::shared_ptr<T> editorTarget() const noexcept;
    std::shared_ptr<filing::NamedObject> editorTargetNamedObject() const noexcept;

private:
    std::shared_ptr<T> _editorTarget;
};
} // namespace ample::gui

#include "templates/TabEditor.hpp"
