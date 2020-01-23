#pragma once

namespace graphics
{
struct ColorRGB
{
    ColorRGB();

    ColorRGB(const double &r, const double &g, const double &b);

    ColorRGB(const double &r, const double &g, const double &b, const double &a);

    double r, g, b, a;
};
} // namespace graphics
