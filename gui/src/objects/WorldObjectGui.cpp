#include <imgui.h>

#include "objects/WorldObjectGui.h"

namespace ample::gui
{
WorldObjectGui::WorldObjectGui(std::shared_ptr<filing::NamedObject> object)
    : _object(std::dynamic_pointer_cast<physics::WorldObject2d>(object)) {}

WorldObjectGui::WorldObjectGui() {}

void WorldObjectGui::onCreate()
{
    // ImGui::InputText("Name", name, 255);
    // ImGui::InputScalar
}
void WorldObjectGui::onSubmitCreate()
{
}
void WorldObjectGui::onEdit()
{
}
void WorldObjectGui::onSubmitEdit()
{
}
void WorldObjectGui::onView()
{
}
void WorldObjectGui::onInspect()
{
}
void WorldObjectGui::onPreview()
{
}
std::string WorldObjectGui::name() const
{
    ASSERT(_object);
    return _object->name();
}
std::string WorldObjectGui::className() const
{
    return "WorldObject2d";
}
} // namespace ample::gui
