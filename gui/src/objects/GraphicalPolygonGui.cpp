#include <imgui.h>

#include "objects/GraphicalPolygonGui.h"

namespace ample::gui
{
GraphicalPolygonGui::GraphicalPolygonGui(std::shared_ptr<filing::NamedObject> polygon)
    : _polygon(std::dynamic_pointer_cast<graphics::GraphicalPolygon>(polygon)) {}

GraphicalPolygonGui::GraphicalPolygonGui() {}

void GraphicalPolygonGui::onCreate()
{
    // ImGui::InputText("Name", name, 255);
    // ImGui::InputScalar
}
void GraphicalPolygonGui::onSubmitCreate()
{
}
void GraphicalPolygonGui::onEdit()
{
}
void GraphicalPolygonGui::onSubmitEdit()
{
}
void GraphicalPolygonGui::onView()
{
}
void GraphicalPolygonGui::onInspect()
{
}
void GraphicalPolygonGui::onPreview()
{
}
std::string GraphicalPolygonGui::name() const
{
    ASSERT(_polygon);
    return _polygon->name();
}
std::string GraphicalPolygonGui::className() const
{
    return "GraphicalPolygon";
}
} // namespace ample::gui
