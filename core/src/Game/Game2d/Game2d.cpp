#include <string>

#include "Game2d.h"
#include "GameException.h"
#include "Utils.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window)
    : graphics::LayeredWindowActivity(window),
      _levelSwitchingController(std::make_shared<StateMachine>("game_controller"))
{
    addBehavior(_levelSwitchingController);
}

Game2d::Game2d(window::Window &window, const std::filesystem::path &directory)
    : graphics::LayeredWindowActivity(window),
      _levelSwitchingController(std::make_shared<StateMachine>(filing::JsonIO(filing::openJSONfile("game_controller.json"))))
{
    addBehavior(_levelSwitchingController);
    // setCurrentLevel();
    // TODO
}

void Game2d::saveAs(const std::filesystem::path &path)
{
    std::ofstream gameControllerFile(_path / "game_controller.json");
    // gameControllerFile << _levelSwitchingController->dump();
    // TODO
}

void Game2d::save()
{
    saveAs(_path);
}

std::shared_ptr<game2d::Level> Game2d::createLevel(const std::string &name,
                                                   const float sliceThickness,
                                                   const float physicsLayerPosition,
                                                   const graphics::Vector2d<float> &gravity,
                                                   const std::filesystem::path &destination)
{
    return std::make_shared<game2d::Level>(name,
                                           *_levelSwitchingController,
                                           sliceThickness,
                                           physicsLayerPosition,
                                           gravity,
                                           destination);
}

void Game2d::setCurrentLevel(std::shared_ptr<Level> level)
{
    _levelSwitchingController->setStartState(level);
}

std::shared_ptr<Level> Game2d::currentLevel() const noexcept
{
    return std::static_pointer_cast<Level>(_levelSwitchingController->getCurrentState());
}
} // namespace ample::game::game2d
