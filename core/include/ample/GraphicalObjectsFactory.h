#pragma once

#include "Factory.h"
#include "GraphicalObject2d.h"

namespace ample::game::factory
{
static ample::utils::Factory<graphics::GraphicalObject, const std::string &> GraphicalObjecsFactory;

static ample::utils::Factory<graphics::GraphicalObject, const std::string &>::Register<graphics::GraphicalObject> GraphicalObjectRegister("GraphicalObject");
static ample::utils::Factory<graphics::GraphicalObject, const std::string &>::Register<graphics::GraphicalPolygon> GraphicalPolygonRegister("GraphicalPolygon");
static ample::utils::Factory<graphics::GraphicalObject, const std::string &>::Register<graphics::GraphicalEdge> GraphicalEdgeRegister("GraphicalEdge");
static ample::utils::Factory<graphics::GraphicalObject, const std::string &>::Register<graphics::GraphicalObject2d> GraphicalObject2dRegister("GraphicalObject2d");
} // namespace ample::game::factory
