#include <imgui.h>

#include "objects/SliceGui.h"

namespace ample::gui
{
SliceGui::SliceGui(std::shared_ptr<filing::NamedObject> slice)
    : _slice(std::dynamic_pointer_cast<filing::Scene2d>(slice)) {}

SliceGui::SliceGui() {}

void SliceGui::onCreate()
{
    // ImGui::InputText("Name", name, 255);
    // ImGui::InputScalar
}
void SliceGui::onSubmitCreate()
{
}
void SliceGui::onEdit()
{
}
void SliceGui::onSubmitEdit()
{
}
void SliceGui::onView()
{
}
void SliceGui::onInspect()
{
}
void SliceGui::onPreview()
{
}
std::string SliceGui::name() const
{
    ASSERT(_slice);
    return _slice->name();
}
std::string SliceGui::className() const
{
    return "Scene2d";
}
} // namespace ample::gui
