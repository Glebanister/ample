#include "Shape.h"
#include "JsonIO.h"

namespace ample::geometry
{

Shape::Shape(const std::string &areaType)
    : _areaType(areaType) {}

std::string Shape::dump()
{
    filing::JsonIO result;
    result.write<std::string>("area_type", _areaType);
    return result;
}
} // namespace ample::geometry
