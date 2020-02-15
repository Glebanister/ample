#pragma once

#include <vector>
#include <GL/gl.h>

#include "Vector.h"
#include "WindowObject.h"

namespace graphics
{
class GraphicShape : public WindowObject2d
{
public:
    GraphicShape(const std::vector<std::pair<int, int>> &verts);

    void draw() override;

private:
    std::vector<std::pair<int, int>> _verts;
};
} // namespace graphics
