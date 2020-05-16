#pragma once

#include "ample/FollowObjectAction.h"

#include "objects/ActionGui.h"

namespace ample::gui
{
class FollowObjectActionGui : public ActionGui
{
public:
    FollowObjectActionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    FollowObjectActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

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
    std::shared_ptr<game::stateMachine::actions::FollowObjectAction> _followAction;
    char nameBuffer[255] = {0};
    char cameraName[255] = {0};
    char objectName[255] = {0};
};
} // namespace ample::gui
