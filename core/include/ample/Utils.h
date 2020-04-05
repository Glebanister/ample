#pragma once

#include <algorithm>

namespace ample::utils
{
template <class T>
void ignore(const T &) {}

template <typename T>
void limit(T &value, const T &min, const T &max)
{
    value = std::min(max, value);
    value = std::max(min, value);
}
} // namespace ample::utils
