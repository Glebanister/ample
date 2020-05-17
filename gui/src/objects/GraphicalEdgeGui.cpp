#include <imgui.h>

#include "objects/GraphicalEdgeGui.h"

namespace ample::gui
{
GraphicalEdgeGui::GraphicalEdgeGui(std::shared_ptr<filing::NamedObject> edge)
    : _edge(std::dynamic_pointer_cast<graphics::GraphicalEdge>(edge)) {}

GraphicalEdgeGui::GraphicalEdgeGui() {}

void GraphicalEdgeGui::onCreate()
{
    // ImGui::InputText("Name", name, 255);
    // ImGui::InputScalar
}
void GraphicalEdgeGui::onSubmitCreate()
{
}
void GraphicalEdgeGui::onEdit()
{
}
void GraphicalEdgeGui::onSubmitEdit()
{
}
void GraphicalEdgeGui::onView()
{
}
void GraphicalEdgeGui::onInspect()
{
}
void GraphicalEdgeGui::onPreview()
{
}
std::string GraphicalEdgeGui::name() const
{
    ASSERT(_edge);
    return _edge->name();
}
std::string GraphicalEdgeGui::className() const
{
    return "GraphicalEdge";
}
} // namespace ample::gui
