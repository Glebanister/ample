#include <imgui.h>

#include "objects/GraphicalObjectGui.h"

namespace ample::gui
{
GraphicalObjectGui::GraphicalObjectGui(std::shared_ptr<filing::NamedObject> object)
    : _object(std::dynamic_pointer_cast<graphics::GraphicalObject>(object)) {}

GraphicalObjectGui::GraphicalObjectGui() {}

void GraphicalObjectGui::onCreate()
{
    // ImGui::InputText("Name", name, 255);
    // ImGui::InputScalar
}
void GraphicalObjectGui::onSubmitCreate()
{
}
void GraphicalObjectGui::onEdit()
{
}
void GraphicalObjectGui::onSubmitEdit()
{
}
void GraphicalObjectGui::onView()
{
}
void GraphicalObjectGui::onInspect()
{
}
void GraphicalObjectGui::onPreview()
{
}
std::string GraphicalObjectGui::name() const
{
    ASSERT(_object);
    return _object->name();
}
std::string GraphicalObjectGui::className() const
{
    return "GraphicalObject";
}
} // namespace ample::gui
