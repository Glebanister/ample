#include "Activity.h"
#include "Storage.h"
#include "Condition.h"

namespace ample
{
Activity::Activity()
    : onRun(false){};

Storage Activity::run()
{
    for (auto cond : this->conditions)
    {
        cond->init(this);
    }
    this->onRun = true;
    while (this->onRun)
    {
        this->processInput();
        this->updateConditions();
        this->generateOutput();
    }
    return this->storage;
}

void Activity::addCondition(Condition *cond)
{
    conditions.push_back(cond);
}

void Activity::stop()
{
    this->onRun = false;
}

void Activity::updateConditions()
{
    for (auto condition : this->conditions)
    {
        condition->update(this);
    }
}
} // namespace ample
