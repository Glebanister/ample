#pragma once

#include "ample/StateMachine.h"

#include "TabEditor.h"

namespace ample::gui
{
class StateMachineEditor : public TabObjectEditor<game::StateMachine>
{
public:
    using TabObjectEditor<game::StateMachine>::TabObjectEditor;
    void drawInterface() override;
};
} // namespace ample::gui
