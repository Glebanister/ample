#include "CameraAction.h"
#include "Camera.h"
#include "GraphicalObject.h"

namespace ample::game::stateMachine::actions
{
CameraAction::CameraAction(const std::string &name,
                           const std::string &className,
                           const std::string &cameraName)
    : Action(name, className),
      _cameraName(cameraName)
{
}

CameraAction::CameraAction(const filing::JsonIO &input)
    : Action(input),
      _cameraName(input.read<std::string>("camera_name"))
{
}

std::string CameraAction::dump()
{
    filing::JsonIO res = Action::dump();
    res.write("camera_name", _cameraName);
    return res;
}

std::string CameraAction::getCameraName() const noexcept
{
    return _cameraName;
}
void CameraAction::setCameraName(const std::string &s) noexcept
{
    _cameraName = s;
}
} // namespace ample::game::stateMachine::actions
