#include <imgui.h>
#include <imnodes.h>

#include "Utils.h"
#include "objects/CollisionTransitionGui.h"

namespace ample::gui
{
CollisionTransitionGui::CollisionTransitionGui(std::shared_ptr<filing::NamedObject> sm, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : TransitionGui(sm, editor, storage),
      _transition(std::dynamic_pointer_cast<game::stateMachine::transitions::CollisionTransition>(sm))
{
}

CollisionTransitionGui::CollisionTransitionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : TransitionGui(editor, storage)
{
}

void CollisionTransitionGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
}

void CollisionTransitionGui::onSubmitCreate()
{
    if (!_nextState)
    {
        throw game::GameException("Next state is not set");
    }
    // _transition = std::make_shared<game::stateMachine::transitions::CollisionTransition>(nameBuffer, _nextState, milliseconds);
    _baseTransition = _transition;
}

void CollisionTransitionGui::onEdit()
{
    ASSERT(_transition);
    // gui_utils::InputScalar("Time, ms", milliseconds, 10, 0, INT32_MAX - 1);
}

void CollisionTransitionGui::onSubmitEdit()
{
    // _transition->setTimeDelta(milliseconds);
}

void CollisionTransitionGui::onView()
{
}

void CollisionTransitionGui::onInspect()
{
}

void CollisionTransitionGui::onPreview()
{
    // ImGui::Text("Time, ms: %d", milliseconds);
}

std::string CollisionTransitionGui::name() const
{
    ASSERT(_transition);
    return _transition->name();
}
std::string CollisionTransitionGui::className() const
{
    return "CollisionTransition";
}
} // namespace ample::gui
