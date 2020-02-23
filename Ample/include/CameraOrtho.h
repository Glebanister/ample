#pragma once

#include "Camera.h"

namespace ample::graphics
{
class CameraOrtho : public Camera
{
public:
    CameraOrtho(Vector2d<pixel_t> viewSize, Vector2d<pixel_t> viewPosition,
                      Vector2d<double> cameraSize, Vector3d<double> cameraPosition,
                      double ratio = 1.0);
    CameraOrtho(Vector2d<pixel_t> viewSize, Vector2d<pixel_t> viewPosition,
                      Vector2d<double> cameraSize, Vector2d<double> cameraPosition,
                      double ratio = 1.0);
    CameraOrtho(Vector2d<pixel_t> viewSize,
                      Vector2d<double> cameraSize,
                      double ratio = 1.0);
    CameraOrtho(Vector2d<pixel_t> cameraSize, double ratio = 1.0);

    void look() override;
    void unlook() override;
};
} // namespace ample::graphics
