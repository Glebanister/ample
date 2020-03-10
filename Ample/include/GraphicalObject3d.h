#pragma once

#include "GraphicalObject.h"

namespace ample::graphics
{
class GraphicalObject3d
{
public:
    void draw(Vector3d<float> &&scaled = {1.0, 1.0, 1.0},
              Vector3d<float> &&rotated = {0.0, 0.0, 0.0},
              Vector3d<float> &&translated = {0.0, 0.0, 0.0}) override;

private:
};
} // namespace ample::graphics
