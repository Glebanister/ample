#pragma once

#include <filesystem>

#include "LayeredWindowActivity.h"
#include "Level.h"
#include "StateMachine.h"

namespace ample::game::game2d
{
class Game2dEditor : public activity::Activity
{
public:
    Game2dEditor();
    Game2dEditor(const std::filesystem::path &existingProjectPath);

    void save();
    void saveAs(const std::filesystem::path &projectPath);

    std::pair<std::shared_ptr<Level>, std::shared_ptr<LevelLoader>> createLevel(
        const std::string &name,
        float sliceThikness,
        float physicsLayerPosition,
        const graphics::Vector2d<float> &gravity);

    std::shared_ptr<StateMachine> createStateMachine(const std::string &name,
                                                     std::shared_ptr<Level> level);

    void showLevel(std::shared_ptr<Level> level);
    std::shared_ptr<Level> getCurrentLevel() const noexcept;
    LevelSwitcher &levelSwitcher() noexcept;
    std::vector<std::shared_ptr<Level>> &getLevelsList() noexcept;

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
