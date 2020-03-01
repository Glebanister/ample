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

    void addCamera(const Camera &);
    void clearCameras();

    virtual void addObject(const GraphicalObject &);
    void clearObjecs();

private:
    std::vector<std::shared_ptr<Camera>> _cameras;
    std::vector<std::shared_ptr<GraphicalObject>> _objects;
};
} // namespace ample::graphics
