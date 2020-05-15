#include <imgui.h>

#include "objects/GraphicalObject2dGui.h"

namespace ample::gui
{
GraphicalObject2dGui::GraphicalObject2dGui(std::shared_ptr<filing::NamedObject> object)
    : _object(std::dynamic_pointer_cast<graphics::GraphicalObject2d>(object)) {}

GraphicalObject2dGui::GraphicalObject2dGui() {}

void GraphicalObject2dGui::onCreate()
{
    // ImGui::InputText("Name", name, 255);
    // ImGui::InputScalar
}
void GraphicalObject2dGui::onSubmitCreate()
{
}
void GraphicalObject2dGui::onEdit()
{
}
void GraphicalObject2dGui::onSubmitEdit()
{
}
void GraphicalObject2dGui::onView()
{
}
void GraphicalObject2dGui::onInspect()
{
}
void GraphicalObject2dGui::onPreview()
{
}
std::string GraphicalObject2dGui::name() const
{
    ASSERT(_object);
    return _object->name();
}
std::string GraphicalObject2dGui::className() const
{
    return "GraphicalObject2d";
}
} // namespace ample::gui
