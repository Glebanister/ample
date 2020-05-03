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
      _levelSwitcher(existingProjectPath)
{
}

void Game2dEditor::saveAs(const std::filesystem::path &projectPath)
{
    if (projectPath.empty())
    {
        throw GameException("project path can not be empty");
    }
    utils::tryCreateDirectory(_projectPath);
    utils::tryCreateDirectory(_projectPath / "levels");
    _levelSwitcher.save(_projectPath);
    for (auto &level : _levels)
    {
        level->saveAs(_projectPath / "levels" / level->name());
    }
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

void Game2dEditor::save()
{
    if (_projectPath.empty())
    {
        throw GameException("set project path to save");
    }
    saveAs(_projectPath);
}

std::shared_ptr<Level> Game2dEditor::createLevel(const std::string &name,
                                                 float sliceThikness,
                                                 float physicsLayerPosition,
                                                 const graphics::Vector2d<float> &gravity)
{

    auto level = std::make_shared<Level>(name,
                                         sliceThikness,
                                         physicsLayerPosition,
                                         gravity,
                                         _projectPath / "name");
    _levels.push_back(level);
    return level;
}

void Game2dEditor::showLevel(std::shared_ptr<Level> level)
{
    _currentLevel = level;
}

LevelSwitcher &Game2dEditor::levelSwitcher() noexcept
{
    return _levelSwitcher;
}
} // namespace ample::game::game2d
