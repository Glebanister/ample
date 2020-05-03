#pragma once

#include "Vector2d.h"
#include "StoredObject.h"

namespace ample::geometry
{
class Shape : public filing::StoredObject
{
public:
    Shape(const std::string &areaType);
    std::string dump() override;
    virtual bool inside(const graphics::Vector2d<float> &) = 0;

private:
    const std::string _areaType;
};
} // namespace ample::Geometry
