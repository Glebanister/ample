#include "FollowObjectAction.h"
#include "Camera.h"
#include "GraphicalObject.h"

namespace ample::game::stateMachine::actions
{
FollowObjectAction::FollowObjectAction(const std::string &name,
                                       const std::string &cameraName,
                                       const std::string &objectName)
    : CameraAction(name, "FollowObjectAction", cameraName),
      _objectName(objectName)
{
}

FollowObjectAction::FollowObjectAction(const filing::JsonIO &input)
    : CameraAction(input),
      _objectName(input.read<std::string>("object_name"))
{
}

std::string FollowObjectAction::dump()
{
    filing::JsonIO res = CameraAction::dump();
    res.write("object_name", _objectName);
    return res;
}

std::string FollowObjectAction::getObjectName() const noexcept
{
    return _objectName;
}

void FollowObjectAction::setObjectName(const std::string &s) noexcept
{
    _objectName = s;
}

void FollowObjectAction::onActive()
{
    auto cam = std::dynamic_pointer_cast<graphics::Camera>(getNamespace().getObject(getCameraName()));
    auto obj = std::dynamic_pointer_cast<graphics::GraphicalObject>(getNamespace().getObject(_objectName));
    cam->setTranslate({obj->getX(), obj->getY(), obj->getZ()});
}
} // namespace ample::game::stateMachine::actions
