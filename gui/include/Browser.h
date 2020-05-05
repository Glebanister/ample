#pragma once

#include <memory>

#include "ample/NamedObject.h"

#include "InterfaceUnit.h"

namespace ample::gui
{
class Browser : public InterfaceUnit<Browser>
{
public:
    void drawInterface() override;

    void setFocus(std::shared_ptr<filing::NamedObject> object);
    filing::NamedObject &getFocusedObject() noexcept;

private:
    std::shared_ptr<filing::NamedObject> _focusedObject;
};
} // namespace ample::gui
