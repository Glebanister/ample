#pragma once

#include <filesystem>

#include "StateMachine.h"
#include "GameException.h"

namespace ample::game
{
class LevelSwitcher : public StateMachine
{
public:
    LevelSwitcher(const std::filesystem::path &projectPath)
        : StateMachine(filing::JsonIO(filing::openJSONfile(projectPath / "level_switcher.json")).read<std::string>("name"),
                       "LevelSwitcher")
    {
    }

    std::string dump() override
    {
        if (!_startState)
        {
            throw GameException{"state machine start state has not been recorded, dump can not be handled"};
        }
        filing::JsonIO output = NamedStoredObject::dump();
        output.write<std::string>("start_state", _startState->name());
        std::vector<std::string> statesStrings;
        std::unordered_map<std::string, bool> used;
        _startState->dumpRecursive(statesStrings, used);
        return filing::mergeStrings({output, filing::makeField("states", filing::dumpObjectsVector(statesStrings))});
    }
};
} // namespace ample::game
