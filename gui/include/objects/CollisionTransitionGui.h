#pragma once

#include <memory>

#include "ample/CollisionTransition.h"
#include "ample/Game2dEditor.h"

#include "ObjectGui.h"
#include "ObjectStorageGui.h"
#include "TransitionGui.h"

namespace ample::gui
{
class ObjectStorageGui;
class CollisionTransitionGui : public TransitionGui
{
public:
    CollisionTransitionGui(std::shared_ptr<filing::NamedObject>,
                           std::shared_ptr<game::game2d::Game2dEditor> editor,
                           ObjectStorageGui *);
    CollisionTransitionGui(std::shared_ptr<game::game2d::Game2dEditor> editor,
                           ObjectStorageGui *);

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
    std::shared_ptr<game::stateMachine::transitions::CollisionTransition> _transition;
    char nameBuffer[255];
};
} // namespace ample::gui
