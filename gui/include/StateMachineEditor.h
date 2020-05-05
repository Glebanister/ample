#pragma once

#include "ample/StateMachine.h"

#include "TabEditor.h"

namespace ample::gui
{
class StateMachineEditor : public TabEditor
{
public:
    StateMachineEditor(std::shared_ptr<game::StateMachine>);

    void drawInterface() override;
};
} // namespace ample::gui
