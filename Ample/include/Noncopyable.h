#pragma once

namespace ample::utils
{
class Noncopyable
{
    Noncopyable(const Noncopyable &other) = delete;
    Noncopyable &operator=(const Noncopyable &other) = delete;
};
} // namespace ample::utils
