#include "Color.h"

namespace ample::graphics
{
Color::Color(int32_t red, int32_t green, int32_t blue, int32_t alpha)
    : r(red), g(green), b(blue), a(alpha) {}

Color::Color()
    : r(255), g(255), b(255), a(255) {}

Color::Color(int32_t hex, int32_t alpha)
    : r((hex >> 16) & 0xFF),
      g((hex >> 8) & 0xFF),
      b(hex & 0xFF),
      a(alpha) {}

} // namespace ample::graphics
