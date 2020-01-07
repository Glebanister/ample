#include <cassert>
#include <exception>

#include "Activity.h"
#include "Storage.h"
#include "LogicBlock.h"

namespace ample
{
Activity::Activity()
    : onRun(false){};

void Activity::init()
{
    return;
}

void Activity::terminate()
{
    return;
}

Storage Activity::mainLoop()
{
    this->init();
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
    this->terminate();
    return this->storage;
}

void Activity::addLogicBlock(LogicBlock *cond)
{
    if (!cond)
    {
        throw std::runtime_error(__FUNCTION__);
    }
    conditions.push_back(cond);
}

void Activity::clearConditions()
{
    conditions.clear();    
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
