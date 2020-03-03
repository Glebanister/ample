#pragma once

namespace ample::utils
{
class Singleton
{
public:
    static Singleton &instance();
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    Singleton() {}
    ~Singleton() {}
};
} // namespace ample::utils
