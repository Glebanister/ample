#pragma once

#include <filesystem>

#include "LayeredWindowActivity.h"
#include "Level.h"

namespace ample::game::game2d
{
class Game2dEditor : public graphics::LayeredWindowActivity
{
public:
    Game2dEditor(window::Window &window);
    Game2dEditor(window::Window &window,
                 const std::filesystem::path &existingProjectPath);

    void save();
    void saveAs(const std::filesystem::path &projectPath);

    std::pair<std::shared_ptr<Level>, std::shared_ptr<LevelLoader>> createLevel(
        const std::string &name,
        float sliceThikness,
        float physicsLayerPosition,
        const graphics::Vector2d<float> &gravity);

    void showLevel(std::shared_ptr<Level> level);
    std::shared_ptr<Level> getCurrentLevel() const noexcept;
    LevelSwitcher &levelSwitcher() noexcept;

    void setProjectPath(const std::filesystem::path &path);
    std::filesystem::path getProjectPath() const noexcept;

    void onActive() override;

private:
    LevelSwitcher _levelSwitcher;
    std::filesystem::path _projectPath = "";
    std::vector<std::shared_ptr<Level>> _levels;
    std::shared_ptr<Level> _currentLevel = nullptr;
    bool _prepared = false;
};
} // namespace ample::game::game2d
