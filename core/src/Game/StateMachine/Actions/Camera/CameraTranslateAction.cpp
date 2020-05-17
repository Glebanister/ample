#include "CameraTranslateAction.h"
#include "Camera.h"

namespace ample::game::stateMachine::actions
{
CameraTranslateAction::CameraTranslateAction(const std::string &name,
                                             const std::string &cameraName,
                                             const graphics::Vector3d<float> &vector)
    : CameraAction(name, "CameraTranslateAction", cameraName),
      _vector(vector)
{
}

CameraTranslateAction::CameraTranslateAction(const filing::JsonIO &input)
    : CameraAction(input),
      _vector(input.read<graphics::Vector3d<float>>("vector"))
{
}

std::string CameraTranslateAction::dump()
{
    filing::JsonIO res = CameraAction::dump();
    res.write("vector", _vector);
    return res;
}

graphics::Vector3d<float> CameraTranslateAction::getVector() const noexcept
{
    return _vector;
}

void CameraTranslateAction::setVector(const graphics::Vector3d<float> &v) noexcept
{
    _vector = v;
}

void CameraTranslateAction::onActive()
{
    auto cam = std::dynamic_pointer_cast<graphics::Camera>(getNamespace().getObject(getCameraName()));
    cam->translate({_vector.x, _vector.y, _vector.z});
}
} // namespace ample::game::stateMachine::actions
