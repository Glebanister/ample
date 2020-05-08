#pragma once

#include <memory>

#include "ample/StateMachine.h"

#include "objects/ObjectGui.h"

namespace ample::gui
{
class StateMachineGui : public ObjectGui
{
public:
    StateMachineGui(std::shared_ptr<filing::NamedObject>);
    StateMachineGui();

    void onCreate() override;
    void onSubmitCreate() override;
    void onEdit() override;
    void onSubmitEdit() override;
    void onView() override;
    void onInspect() override;
    void onPreview() override;

    std::string name() const override;
    std::string className() const override;

private:
    std::shared_ptr<game::StateMachine> _sm;

    char nameBuffer[255];
    
};
} // namespace ample::gui
