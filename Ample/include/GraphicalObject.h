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

    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual float getZ() const = 0;

    virtual float getAngleX() const = 0;
    virtual float getAngleY() const = 0;
    virtual float getAngleZ() const = 0;

    virtual float getScaleX() const = 0;
    virtual float getScaleY() const = 0;
    virtual float getScaleZ() const = 0;

    void setRatio(float);
    float getRatio() const;

protected:
    std::vector<GraphicalObject *> _subObjects;
    float _ratio = 1.0;
};
} // namespace ample::graphics
