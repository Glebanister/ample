#pragma once

#include <vector>

#include "Vector2d.h"
#include "Utils.h"

namespace ample::geometry
{
template <typename T = float>
std::vector<graphics::Vector2d<T>> VectorRectangle(const graphics::Vector2d<T> &size,
                                                   const graphics::Vector2d<T> &origin = {0, 0});
} // namespace ample::geometry

#include "templates/VectorRectangle.hpp"
