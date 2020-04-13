#include <iostream>
#include <memory>

#include "Scene2d.h"
#include "Exception.h"
#include "Debug.h"
#include "JsonIO.h"
#include "CameraOrtho.h"
#include "CameraPerspective.h"

namespace ample::filing
{

Scene2d::Scene2d(const std::string &name,
                 const ample::graphics::Vector2d<float> &gravity,
                 float z,
                 float thickness,
                 float relativePositionInSlice)
    : WorldLayer2d(gravity, z, thickness, relativePositionInSlice),
      NamedStoredObject(name, "Scene2d"),
      _gravity(gravity),
      _zPosition(z),
      _sceneThickness(thickness),
      _relativeSlicePosition(relativePositionInSlice)
{
}

Scene2d::Scene2d(const JsonIO &input)
    : Scene2d(input.read<std::string>("name"),
              input.read<graphics::Vector2d<float>>("gravity"),
              input.read<float>("z"),
              input.read<float>("thickness"),
              input.read<float>("relative_position_in_slice"))
{
    auto objectStrings = filing::loadObjectsVector(input.read<std::string>("objects"));
    auto cameraStrings = filing::loadObjectsVector(input.read<std::string>("cameras"));
    for (const auto &objString : objectStrings)
    {
        // addObject();
        // addWorldJoint();
        // addWorldObject(); // TODO
    }
    for (const auto &cameraString : cameraStrings)
    {
        std::string cameraType = JsonIO(cameraString).read<std::string>("className");
        // TODO: use Factory<Camera> !!!
        if (cameraType == "CameraOrtho")
        {
            addCamera(std::make_shared<graphics::CameraOrtho>(cameraString));
        }
        else if (cameraType == "CameraPerspective")
        {
            addCamera(std::make_shared<graphics::CameraPerspective>(cameraString));
        }
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
        objectStrings.push_back(camera->dump());
    }
    JsonIO output;
    output.write<graphics::Vector2d<float>>("gravity", _gravity);
    output.write<float>("z", _zPosition);
    output.write<float>("thickness", _sceneThickness);
    output.write<float>("relative_position_in_slice", _relativeSlicePosition);
    output.write<std::string>("objects", filing::dumpObjectsVector(objectStrings));
    output.write<std::string>("cameras", filing::dumpObjectsVector(cameraStrings));
    return output;
}

float Scene2d::getDistance() const
{
    return _zPosition;
}
} // namespace ample::filing
