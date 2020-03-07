#pragma once

#include <vector>
#include <memory>

#include "Activity.h"
#include "Vector3d.h"

namespace ample::graphics
{
class GraphicalObject : public activity::Activity
{
public:
    virtual void draw(Vector3d<float> &&scaled = {1.0, 1.0, 1.0},
                      Vector3d<float> &&rotated = {0.0, 0.0, 0.0},
                      Vector3d<float> &&translated = {0.0, 0.0, 0.0}) = 0;
    void addSubObject(GraphicalObject &object);

protected:
    std::vector<GraphicalObject *> _subObjects;
};
} // namespace ample::graphics
