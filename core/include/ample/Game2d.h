#pragma once

#include <filesystem>
#include <memory>
#include <unordered_map>

#include "CameraOrtho.h"
#include "CameraPerspective.h"
#include "Debug.h"
#include "GameController.h"
#include "GameException.h"
#include "LayeredWindowActivity.h"
#include "Level.h"
#include "Vector2d.h"
#include "WorldLayer2d.h"

namespace ample::game
{
class GameController;
}

namespace ample::game::game2d
{
class Level;
}

/*

*/

namespace ample::game::game2d
{
class Game2d : public graphics::LayeredWindowActivity
{
public:
    Game2d(window::Window &window);
    Game2d(window::Window &window, const std::filesystem::path &path);
    void save();
    void saveAs(const std::filesystem::path &path);

    GameController &controller() noexcept;
    std::shared_ptr<GameController> controllerPointer() const noexcept;
    std::shared_ptr<game2d::Level> createLevel(const std::string &name,
                                               const float sliceThickness,
                                               const float physicsLayerPosition,
                                               const graphics::Vector2d<float> &gravity,
                                               const std::filesystem::path &destination);
    void setCurrentLevel(std::shared_ptr<Level>);
    std::shared_ptr<Level> currentLevel() const noexcept;

private:
    std::shared_ptr<GameController> _gameController;
    const std::filesystem::path _path;
};
} // namespace ample::game::game2d
