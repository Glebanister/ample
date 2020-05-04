#include "DemoGame.h"
#include "LevelLoader.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::game::game2d::Game2dEditor(window, "example")
{
    setProjectPath("example");
    auto [level, loader] = createLevel("first", 10.0f, 0.5f, {0.0f, -10.0f});
    levelSwitcher().setStartState(loader);
    saveAs("example2");
}
