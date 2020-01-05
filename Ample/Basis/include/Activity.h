#pragma once

#include <vector>

#include "Storage.h"
#include "Condition.h"

namespace ample
{

class Condition;

class Activity
{
public:
    Activity();
    virtual Storage run();
    void stop();

    void addCondition(Condition *cond);

    virtual void processInput() = 0;
    virtual void updateConditions();
    virtual void generateOutput() = 0;

protected:
    bool onRun;
    std::vector<Condition *> conditions;
    Storage storage;
};

} // namespace ample
