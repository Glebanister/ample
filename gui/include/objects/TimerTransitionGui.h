#pragma once

#include <memory>

#include "ample/Game2dEditor.h"
#include "ample/TimerTransition.h"

#include "ObjectGui.h"
#include "ObjectStorageGui.h"
#include "TransitionGui.h"

namespace ample::gui
{
class ObjectStorageGui;
class TimerTransitionGui : public TransitionGui
{
public:
    TimerTransitionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    TimerTransitionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

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
    std::shared_ptr<game::TimerTransition> _transition;
    char nameBuffer[255];
    int32_t milliseconds = 1000;
};
} // namespace ample::gui
