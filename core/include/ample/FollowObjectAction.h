#pragma once

#include "CameraAction.h"

namespace ample::game::stateMachine::actions
{
class FollowObjectAction : public CameraAction
{
public:
    FollowObjectAction(const std::string &name,
                       const std::string &cameraName,
                       const std::string &objectName);
    FollowObjectAction(const filing::JsonIO &input);
    std::string dump() override;

    std::string getObjectName() const noexcept;
    void setObjectName(const std::string &) noexcept;

    void onActive() override;

private:
    std::string _objectName;
};
} // namespace ample::game::stateMachine::actions
