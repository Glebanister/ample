#pragma once

#include "Action.h"

namespace ample::game::stateMachine::actions
{
class CameraAction : public Action
{
public:
    CameraAction(const std::string &name,
                 const std::string &className,
                 const std::string &cameraName);
    CameraAction(const filing::JsonIO &input);
    std::string dump() override;

    std::string getCameraName() const noexcept;
    void setCameraName(const std::string &) noexcept;

private:
    std::string _cameraName;
};
} // namespace ample::game::stateMachine::actions
