#include "Game2dEditor.h"
#include "GameException.h"
#include "Utils.h"

namespace ample::game::game2d
{

Game2dEditor::Game2dEditor(window::Window &window)
    : LayeredWindowActivity(window),
      _levelSwitcher()
{
}

Game2dEditor::Game2dEditor(window::Window &window,
                           const std::filesystem::path &existingProjectPath)
    : LayeredWindowActivity(window),
      _levelSwitcher(existingProjectPath),
      _projectPath(existingProjectPath)
{
    for (const auto &entry : std::filesystem::directory_iterator(existingProjectPath / "levels"))
    {
        if (entry.is_directory())
        {
            _levels.emplace_back(std::make_shared<Level>(entry));
        }
        if (_levels.back()->name() == _levelSwitcher.getCurrentState()->name())
        {
            showLevel(_levels.back());
        }
    }
}

void Game2dEditor::saveAs(const std::filesystem::path &projectPath)
{
    if (projectPath.empty())
    {
        throw GameException("project path can not be empty");
    }
    utils::tryCreateDirectory(projectPath);
    utils::tryCreateDirectory(projectPath / "levels");
    for (auto &level : _levels)
    {
        level->saveAs(projectPath / "levels" / level->name());
    }
    _levelSwitcher.save(projectPath);
}

void Game2dEditor::setProjectPath(const std::filesystem::path &path)
{
    if (_prepared)
    {
        throw GameException("project path can not be changed");
    }
    _projectPath = path;
}

std::filesystem::path Game2dEditor::getProjectPath() const noexcept
{
    return _projectPath;
}

std::vector<std::shared_ptr<Level>> &Game2dEditor::getLevelsList() noexcept
{
    return _levels;
}

void Game2dEditor::save()
{
    if (_projectPath.empty())
    {
        throw GameException("set project path to save");
    }
    saveAs(_projectPath);
}

std::pair<std::shared_ptr<Level>, std::shared_ptr<LevelLoader>> Game2dEditor::createLevel(
    const std::string &name,
    float sliceThikness,
    float physicsLayerPosition,
    const graphics::Vector2d<float> &gravity)
{
    if (getProjectPath().empty())
    {
        throw GameException("set project path to create levels");
    }
    auto level = std::make_shared<Level>(name,
                                         sliceThikness,
                                         physicsLayerPosition,
                                         gravity);
    _levels.push_back(level);
    auto levelLoader = std::make_shared<ample::game::LevelLoader>(getProjectPath(),
                                                                  level->name(),
                                                                  levelSwitcher());
    if (!_levelSwitcher.hasStartState())
    {
        _levelSwitcher.setStartState(levelLoader);
    }
    return {level, levelLoader};
}

std::shared_ptr<StateMachine> Game2dEditor::createStateMachine(const std::string &name,
                                                               std::shared_ptr<Level> level)
{
    return level->createStateMachine(name);
}

void Game2dEditor::onActive()
{
    LayeredWindowActivity::onActive();
    if (_currentLevel)
    {
        _currentLevel->onActive();
    }
}

void Game2dEditor::showLevel(std::shared_ptr<Level> level)
{
    _currentLevel = level;
}

std::shared_ptr<Level> Game2dEditor::getCurrentLevel() const noexcept
{
    return _currentLevel;
}

LevelSwitcher &Game2dEditor::levelSwitcher() noexcept
{
    return _levelSwitcher;
}
} // namespace ample::game::game2d
