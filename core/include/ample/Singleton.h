#pragma once

namespace ample::utils
{
template <typename T>
class Singleton
{
public:
    static T &instance()
    {
        struct T_Proxy : public T
        {
            T_Proxy() : T() {}
        };
        static T_Proxy inst;
        return inst;
    }

    Singleton &operator=(Singleton const &) = delete;
    Singleton &operator=(Singleton &&) = delete;

protected:
    Singleton() = default;
};
} // namespace ample::utils
