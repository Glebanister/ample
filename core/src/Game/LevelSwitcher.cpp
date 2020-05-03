#include <iostream>

#include "LevelSwitcher.h"
#include "Utils.h"

namespace ample::game
{


LevelSwitcher::LevelSwitcher(const std::filesystem::path &projectPath)
    : StateMachine("level_switcher"),
      _projectPath(projectPath)
{
    filing::JsonIO switcherFile = filing::openJSONfile(projectPath / "level_switcher.json");
    std::string startLevelName = switcherFile.read<std::string>("start_level");
    for (const auto &entry : std::filesystem::directory_iterator(projectPath / "levels"))
    {
        auto newScene = std::make_shared<filing::Scene2d>(filing::openJSONfile(entry.path()), levelNamespace); // fill level namespace
        _sliceByDistance[newScene->getDistance()] = newScene;
        newScene->setVisibility(false);
        addBehavior(newScene);
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
    std::filesystem::path filename = path / "levels" / level->name();
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

void LevelSwitcher::save()
{
    utils::tryCreateFile(_projectPath / "level_switcher.json");
    std::ofstream levelSwitcherFile(_projectPath / "level_switcher.json");
    levelSwitcherFile << dump();
}

std::string LevelSwitcher::dump()
{
    if (!_startState)
    {
        throw GameException{"start level has not been recorded, dump can not be handled"};
    }
    filing::JsonIO output = NamedStoredObject::dump();
    output.write<std::string>("start_level", _startState->name());
    std::unordered_map<std::string, bool> used;
    dumpLevelsRecursive(_startState, used, _projectPath);
    return output;
}
} // namespace ample::game
