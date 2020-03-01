#pragma once

#include <vector>
#include <memory>

#include "GraphicalObject.h"
#include "Camera.h"
#include "Activity.h"

namespace ample::graphics
{
class Layer : public activity::Activity
{
public:
    void onActive() override;

    template <class TCamera>
    void addCamera(const TCamera &camera)
    {
        _cameras.push_back(std::make_shared<TCamera>(camera));
    }
    void clearCameras();

    template <class TGraphicalObject>
    void addObject(const TGraphicalObject &object)
    {
        activity::Activity::addActivity(object);
        _objects.push_back(std::make_shared<TGraphicalObject>(object));
    }
    void clearObjecs();

private:
    std::vector<std::shared_ptr<Camera>> _cameras;
    std::vector<std::shared_ptr<GraphicalObject>> _objects;
};
} // namespace ample::graphics
