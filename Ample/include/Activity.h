#pragma once

#include <vector>

#include "Storage.h"
#include "LogicBlock.h"

namespace ample
{

class LogicBlock;

class Activity
{
public:
    Activity();
    virtual void init();
    virtual void terminate();

    virtual Storage mainLoop();
    void stop();

    void addLogicBlock(LogicBlock *cond);
    void clearConditions();

    virtual void processInput() = 0;
    virtual void updateConditions();
    virtual void generateOutput() = 0;

protected:
    bool onRun;
    std::vector<LogicBlock *> conditions;
    Storage storage;
};

} // namespace ample
