#include "Singleton.h"

namespace ample::utils
{
Singleton &Singleton::instance()
{
    static Singleton singleton;
    return singleton;
}
} // namespace ample::utils
