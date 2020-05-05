#pragma once

#include "ample/NamedObject.h"

namespace ample::gui
{
class TabEditor
{
public:
    TabEditor(std::shared_ptr<filing::NamedObject>);
    virtual void drawInterface() = 0;
    std::shared_ptr<filing::NamedObject> editorTarget() const noexcept;

private:
    std::shared_ptr<filing::NamedObject> _editorTarget;
};
}
