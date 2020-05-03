#pragma once

#include "Circle.h"
#include "Factory.h"
#include "Point.h"
#include "Rectangle.h"

namespace ample::game::factory
{
static ample::utils::Factory<geometry::Shape, const std::string &> ShapesFactory;

static ample::utils::Factory<geometry::Shape, const std::string &>::Register<geometry::Circle> CircleShapeRegister("Circle");
static ample::utils::Factory<geometry::Shape, const std::string &>::Register<geometry::Point> PointShapeRegister("Point");
static ample::utils::Factory<geometry::Shape, const std::string &>::Register<geometry::Rectangle> RectangleShapeRegister("Rectangle");
} // namespace ample::game::factory
