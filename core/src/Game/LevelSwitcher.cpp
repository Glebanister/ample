#include <iostream>

#include "LevelSwitcher.h"
#include "TransitionsFactory.h"
#include "Utils.h"

namespace ample::game
{
LevelSwitcher::LevelSwitcher()
    : StateMachine("level_swithcer", "LevelSwitcher") {}

LevelSwitcher::LevelSwitcher(const std::filesystem::path &projectPath)
    : LevelSwitcher()
{
    std::vector<std::string> stateStrings;
    std::vector<std::filesystem::path> statePaths;
    for (const auto &entry : std::filesystem::directory_iterator(projectPath / "levels"))
    {
        if (entry.is_directory())
        {
            std::filesystem::path levelPath = entry.path() / "level_state.json";
            utils::tryOpenFile(levelPath);
            stateStrings.push_back(utils::readAllFile(levelPath));
            statePaths.push_back(entry.path());
        }
    }

    std::string startStateName = filing::JsonIO(
                                     filing::openJSONfile(projectPath / "level_switcher.json"))
                                     .read<std::string>("start_level");

    std::unordered_map<std::string, std::shared_ptr<LevelLoader>> statesMap;
    for (size_t i = 0; i < stateStrings.size(); ++i)
    {
        auto loader = std::make_shared<LevelLoader>(statePaths[i], *this);
        if (loader->levelName() == startStateName)
        {
            setStartState(loader);
        }
        statesMap[loader->levelName()] = loader;
    }
    for (const filing::JsonIO &stateData : stateStrings)
    {
        auto transitionStrings = filing::loadObjectsVector(stateData.updateJsonIO("transitions"));
        auto currentState = statesMap[stateData.read<std::string>("name")];
        for (const filing::JsonIO &transitionData : transitionStrings)
        {
            std::string transitionClass = transitionData.read<std::string>("class_name");
            auto nextState = statesMap[transitionData.read<std::string>("to")];
            currentState->addTransition(
                game::factory::TransitionsFactory.produce(
                    transitionClass,
                    transitionData.getJSONstring(),
                    nextState));
        }
    }
}

void dumpLevelsRecursive(std::shared_ptr<StateMachine::State> level,
                         std::unordered_map<std::string, bool> used,

                         const std::filesystem::path path)
{
    if (used[level->name()])
    {
        return;
    }
    used[level->name()] = true;
    utils::tryCreateDirectory(path / "levels" / level->name());
    std::filesystem::path filename = path / "levels" / level->name() / "level_state.json";
    utils::tryCreateFile(filename);
    filing::JsonIO result = level->dump();
    std::vector<std::string> dumpedTransitions;
    for (const auto &transition : level->transitions())
    {
        dumpedTransitions.push_back(transition->dump()); // TODO: may be moved to State::dump()
    }
    result = filing::mergeStrings({
        result,
        filing::makeField("transitions",
                          filing::dumpObjectsVector(dumpedTransitions)),
    });
    for (const auto &transition : level->transitions())
    {
        dumpLevelsRecursive(transition->getNextState(), used, path);
    }
    std::ofstream levelStateFile(filename);
    levelStateFile << result.getJSONstring();
}

bool LevelSwitcher::hasStartState() const noexcept
{
    return _startState.operator bool();
}

void LevelSwitcher::save(const std::filesystem::path &path)
{
    if (!_startState)
    {
        throw GameException{"start level has not been recorded, dump can not be handled"};
    }
    filing::JsonIO output = NamedStoredObject::dump();
    output.write<std::string>("start_level", _startState->name());
    std::unordered_map<std::string, bool> used;
    dumpLevelsRecursive(_startState, used, path);

    utils::tryCreateFile(path / "level_switcher.json");
    std::ofstream levelSwitcherFile(path / "level_switcher.json");
    levelSwitcherFile << output.getJSONstring();
}
} // namespace ample::game
