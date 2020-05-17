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

    graphics::Vector3d<float> getSlowdown() const noexcept;
    void setSlowdown(const graphics::Vector3d<float> &) noexcept;

    void onActive() override;

private:
    std::string _objectName;
    graphics::Vector3d<float> _slowdown = {1.0f, 1.0f, 1.0f};
};
} // namespace ample::game::stateMachine::actions
