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
    secondsId = _transition->getTriggerStartId();
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
    _transition = std::make_shared<game::stateMachine::transitions::CollisionTransition>(nameBuffer, _nextState, std::vector<std::string>{}, 0);
    _baseTransition = _transition;
}

void CollisionTransitionGui::onEdit()
{
    ASSERT(_transition);
    gui_utils::NamedObjectSelector("Add object to action",
                                   newCollidingObject,
                                   _baseTransition->getNamespacePointer()->getAllNames());
    ImGui::SliderInt("Collision blocks delimiter", &secondsId, 0, _transition->getBodyNames().size());
}

void CollisionTransitionGui::onSubmitEdit()
{
    if (newCollidingObject.length())
    {
        _transition->addObjectName(newCollidingObject);
    }
    _transition->setTriggerStartId(secondsId);
}

void CollisionTransitionGui::onView()
{
    TransitionGui::onView();
}

void CollisionTransitionGui::onInspect()
{
}

void CollisionTransitionGui::onPreview()
{
    ImGui::Text("%s", "Colliders:");
    for (int i = 0; i < secondsId; ++i)
    {
        ImGui::Text("%s", _transition->getBodyNames()[i].c_str());
    }
    ImGui::Separator();
    for (size_t i = secondsId; i < _transition->getBodyNames().size(); ++i)
    {
        ImGui::Text("%s", _transition->getBodyNames()[i].c_str());
    }
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
