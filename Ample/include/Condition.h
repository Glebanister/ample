#pragma once

#include "Activity.h"

namespace ample
{
class Activity;

class Condition
{
public:
    virtual int init(Activity *);
    virtual int update(Activity *) = 0;
};
} // namespace ample
