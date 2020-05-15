#include "Color.h"

namespace ample::graphics
{
Color::Color(int32_t red, int32_t green, int32_t blue, int32_t alpha)
    : r(red / 255.0), g(green / 255.0), b(blue / 255.0), a(alpha / 255.0) {}

Color::Color(float red, float green, float blue, float alpha)
    : r(red), g(green), b(blue), a(alpha) {}

Color::Color()
    : Color(255, 255, 255) {}

Color::Color(int32_t hex, int32_t alpha)
    : Color((hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF, alpha) {}

} // namespace ample::graphics
