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

    void addCamera(Camera &camera);
    void clearCameras();

    void addObject(GraphicalObject &object);
    void clearObjecs();

private:
    std::vector<Camera *> _cameras;
    std::vector<GraphicalObject *> _objects;
};
} // namespace ample::graphics