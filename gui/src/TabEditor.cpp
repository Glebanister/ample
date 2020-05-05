#include "TabEditor.h"

namespace ample::gui
{
TabEditor::TabEditor(std::shared_ptr<filing::NamedObject> object)
    : _editorTarget(object) {}

std::shared_ptr<filing::NamedObject> TabEditor::editorTarget() const noexcept
{
    return _editorTarget;
}
} // namespace ample::gui
