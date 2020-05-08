#include <imgui.h>

#include "objects/StateMachineGui.h"

namespace ample::gui
{
StateMachineGui::StateMachineGui(std::shared_ptr<filing::NamedObject> sm)
    : _sm(std::dynamic_pointer_cast<game::StateMachine>(sm)) {}

StateMachineGui::StateMachineGui() {}

void StateMachineGui::onCreate()
{
    // ImGui::InputText("Name", name, 255);
    // ImGui::InputScalar
}
void StateMachineGui::onSubmitCreate()
{
}
void StateMachineGui::onEdit()
{
}
void StateMachineGui::onSubmitEdit()
{
}
void StateMachineGui::onView()
{
}
void StateMachineGui::onInspect()
{
}
void StateMachineGui::onPreview()
{
}
std::string StateMachineGui::name() const
{
    ASSERT(_sm);
    return _sm->name();
}
std::string StateMachineGui::className() const
{
    return "StateMachine";
}
} // namespace ample::gui
