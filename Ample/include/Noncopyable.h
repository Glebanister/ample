#pragma once

namespace ample::utils
{
class Noncopyable
{
public:
    Noncopyable() = default;
    Noncopyable(const Noncopyable &other) = delete;
    Noncopyable &operator=(const Noncopyable &other) = delete;
};
} // namespace ample::utils
