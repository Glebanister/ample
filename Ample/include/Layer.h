#pragma once

#include <vector>
#include <memory>

#include "GraphicalObject.h"
#include "Camera.h"
#include "Activity.h"

namespace ample::graphics
{
class Layer : activity::Activity
{
public:
    void onActive() override;

    void addCamera(std::shared_ptr<Camera>);
    void clearCameras();

    void addObject(std::shared_ptr<GraphicalObject>);
    void addObject(const std::vector<std::shared_ptr<GraphicalObject>> &);
    void clearObjecs();

private:
    std::vector<std::shared_ptr<Camera>> _cameras;
    std::vector<std::shared_ptr<GraphicalObject>> _objects;
};
} // namespace ample::graphics
