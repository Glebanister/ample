#pragma once

#include <cstdint>

namespace ample::graphics
{
struct Color
{
    float r, g, b, a;
    Color(int32_t red, int32_t green, int32_t blue, int32_t alpha = 255);
    Color(int32_t hex, int32_t alpha = 255);
    Color();
};
} // namespace ample::graphics
