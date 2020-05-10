#include <imgui.h>
#include <imnodes.h>

#include "Utils.h"
#include "objects/TimerTransitionGui.h"

namespace ample::gui
{
TimerTransitionGui::TimerTransitionGui(std::shared_ptr<filing::NamedObject> sm, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : TransitionGui(sm, editor, storage),
      _transition(std::dynamic_pointer_cast<game::TimerTransition>(sm))
{
    milliseconds = _transition->getTimeDelta();
}

TimerTransitionGui::TimerTransitionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : TransitionGui(editor, storage)
{
}

void TimerTransitionGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);

    TransitionGui::onCreate();
    gui_utils::InputScalar("Time, ms", milliseconds, 10, 0, INT32_MAX - 1);
}

void TimerTransitionGui::onSubmitCreate()
{
    if (!_nextState)
    {
        throw game::GameException("Next state is not set");
    }
    _transition = std::make_shared<game::TimerTransition>(nameBuffer, _nextState, milliseconds);
    _baseTransition = _transition;
}

void TimerTransitionGui::onEdit()
{
    ASSERT(_transition);
    gui_utils::InputScalar("Time, ms", milliseconds, 10, 0, INT32_MAX - 1);
}

void TimerTransitionGui::onSubmitEdit()
{
    _transition->setTimeDelta(milliseconds);
}

void TimerTransitionGui::onView()
{
}

void TimerTransitionGui::onInspect()
{
}

void TimerTransitionGui::onPreview()
{
    ImGui::Text("Time, ms: %d", milliseconds);
}

std::string TimerTransitionGui::name() const
{
    ASSERT(_transition);
    return _transition->name();
}
std::string TimerTransitionGui::className() const
{
    return "TimerTransition";
}
} // namespace ample::gui
