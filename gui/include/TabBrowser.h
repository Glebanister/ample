#pragma once

#include <memory>

#include "ample/NamedObject.h"

#include "InterfaceUnit.h"

namespace ample::gui
{
class TabBrowser : public GraphicalInterface
{
public:
    virtual std::shared_ptr<filing::NamedObject> browserTargetNamedObject() const noexcept = 0;
};

template <class T>
class TabObjectBrowser : public TabBrowser
{
public:
    TabObjectBrowser(std::shared_ptr<T>);
    std::shared_ptr<T> browserTarget() const noexcept;
    std::shared_ptr<filing::NamedObject> browserTargetNamedObject() const noexcept;

private:
    std::shared_ptr<T> _browserTarget;
};
} // namespace ample::gui

#include "templates/TabBrowser.hpp"
