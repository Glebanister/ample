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
      _objectName(input.read<std::string>("object_name")),
      _slowdown(input.read<graphics::Vector3d<float>>("slowdown"))
{
}

std::string FollowObjectAction::dump()
{
    filing::JsonIO res = CameraAction::dump();
    res.write("object_name", _objectName);
    res.write("slowdown", _slowdown);
    return res;
}

graphics::Vector3d<float> FollowObjectAction::getSlowdown() const noexcept
{
    return _slowdown;
}
void FollowObjectAction::setSlowdown(const graphics::Vector3d<float> &sd) noexcept
{
    _slowdown = sd;
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
    cam->translate({
        (obj->getX() - cam->getX()) * _slowdown.x,
        (obj->getY() - cam->getY()) * _slowdown.y,
        (obj->getZ() - cam->getZ()) * _slowdown.z,
    });
}
} // namespace ample::game::stateMachine::actions
