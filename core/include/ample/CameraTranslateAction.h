#pragma once

#include "CameraAction.h"
#include "Vector3d.h"

namespace ample::game::stateMachine::actions
{
class CameraTranslateAction : public CameraAction
{
public:
    CameraTranslateAction(const std::string &name,
                          const std::string &cameraName,
                          const graphics::Vector3d<float> &vector);
    CameraTranslateAction(const filing::JsonIO &input);
    std::string dump() override;

    graphics::Vector3d<float> getVector() const noexcept;
    void setVector(const graphics::Vector3d<float> &) noexcept;

    void onActive() override;

private:
    graphics::Vector3d<float> _vector;
};
} // namespace ample::game::stateMachine::actions
