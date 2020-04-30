#pragma once

#include "Factory.h"
#include "CameraOrtho.h"
#include "CameraPerspective.h"

namespace ample::game::factory
{
static ample::utils::Factory<graphics::Camera, const std::string &> CamerasFactory;
static ample::utils::Factory<graphics::Camera, const std::string &>::Register<graphics::CameraOrtho> CameraOrthoRegister("CameraOrtho");
static ample::utils::Factory<graphics::Camera, const std::string &>::Register<graphics::CameraPerspective> CameraPerspectiveRegister("CameraPerspective");
} // namespace ample::game::factory
