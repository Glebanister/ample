#include "Colors.h"

namespace graphics
{
ColorRGB::ColorRGB()
    : r(0), g(0), b(0), a(1) {}

ColorRGB::ColorRGB(const double &r, const double &g, const double &b)
    : r(r), g(g), b(b), a(1) {}

ColorRGB::ColorRGB(const double &r, const double &g, const double &b, const double &a)
    : r(r), g(g), b(b), a(a) {}

} // namespace graphics
