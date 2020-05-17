#include <iostream>
#include <memory>

#include "CameraOrtho.h"
#include "CameraPerspective.h"
#include "CamerasFactory.h"
#include "Debug.h"
#include "Exception.h"
#include "GraphicalObjectsFactory.h"
#include "JointsFactory.h"
#include "JsonIO.h"
#include "Scene2d.h"
#include "WorldObjectsFactory.h"

namespace ample::filing
{
Scene2d::Scene2d(const std::string &name,
                 const ample::graphics::Vector2d<float> &gravity,
                 float z,
                 float thickness,
                 float relativePositionInSlice,
                 std::shared_ptr<game::Namespace> ns)
    : WorldLayer2d(gravity, z, thickness, relativePositionInSlice, ns),
      NamedStoredObject(name, "Scene2d"),
      _gravity(gravity),
      _zPosition(z),
      _sceneThickness(thickness),
      _relativeSlicePosition(relativePositionInSlice)
{
}

Scene2d::Scene2d(const JsonIO &input,
                 std::shared_ptr<game::Namespace> globalNamespace)
    : WorldLayer2d(input.read<graphics::Vector2d<float>>("gravity"),
                   input.read<float>("z_position"),
                   input.read<float>("thickness"),
                   input.read<float>("relative_position_in_slice"),
                   globalNamespace),
      NamedStoredObject(input),
      _gravity(input.read<graphics::Vector2d<float>>("gravity")),
      _zPosition(input.read<float>("z_position")),
      _sceneThickness(input.read<float>("thickness")),
      _relativeSlicePosition(input.read<float>("relative_position_in_slice"))
{
    auto objectStrings = filing::loadObjectsVector(input.updateJsonIO("objects"));
    auto cameraStrings = filing::loadObjectsVector(input.updateJsonIO("cameras"));
    for (const auto &objString : objectStrings)
    {
        std::string objectClass = JsonIO(objString).read<std::string>("class_name");
        if (objectClass == "WorldObject2d")
        {
            std::shared_ptr<physics::WorldObject2d> object =
                game::factory::WorldObjecsFactory.produce(objectClass,
                                                          objString,
                                                          *this);
            addWorldObject(object);
        }
        else
        {
            std::shared_ptr<graphics::GraphicalObject> object =
                game::factory::GraphicalObjecsFactory.produce(objectClass,
                                                              objString);
            addObject(object);
        }
        // addWorldJoint(); // TODO
    }
    for (const auto &cameraString : cameraStrings)
    {
        std::string cameraType = JsonIO(cameraString).read<std::string>("class_name");
        std::shared_ptr<graphics::Camera> camera = game::factory::CamerasFactory.produce(cameraType, cameraString);
        addCamera(camera);
    }
}

std::string Scene2d::dump()
{
    std::vector<std::string> objectStrings;
    std::vector<std::string> cameraStrings;
    // TODO: iterators
    for (const auto &object : objects())
    {
        objectStrings.push_back(object->dump());
    }
    for (const auto &camera : _cameras)
    {
        cameraStrings.push_back(camera->dump());
    }
    JsonIO output{NamedStoredObject::dump()};
    output.write<graphics::Vector2d<float>>("gravity", _gravity);
    output.write<float>("z_position", _zPosition);
    output.write<float>("thickness", _sceneThickness);
    output.write<float>("relative_position_in_slice", _relativeSlicePosition);
    return filing::mergeStrings({
        output,
        filing::makeField("objects", filing::dumpObjectsVector(objectStrings)),
        filing::makeField("cameras", filing::dumpObjectsVector(cameraStrings)),
    });
}

float Scene2d::getDistance() const
{
    return _zPosition;
}
} // namespace ample::filing
