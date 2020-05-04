#include "DemoGame.h"
#include "LevelLoader.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::game::game2d::Game2dEditor(window, "example")
{
    // setProjectPath("example");
    // auto level = createLevel("first", 10.0f, 0.5f, {0.0f, -10.0f});
    // auto levelLoader = std::make_shared<ample::game::LevelLoader>(getProjectPath(), "first", levelSwitcher());
    // levelSwitcher().setStartState(levelLoader);
    // firstLevel = Game2d::createLevel("first", 10.0f, 0.5f, {0.0f, -10.0f}, "first_level");
    // setCurrentLevel(firstLevel);
    // auto obj = std::shared_ptr<ample::physics::WorldObject2d>(new ample::physics::WorldObject2d("ground",
    //                                                                                             firstLevel->frontSlice(),
    //                                                                                             ample::physics::BodyType::STATIC_BODY,
    //                                                                                             {{30, 10}, {30, -5}, {-30, -5}, {-30, 2}},
    //                                                                                             1.0,
    //                                                                                             {10.0f, 5.0f},
    //                                                                                             {1.0f, 10.0f},
    //                                                                                             ample::graphics::normalsMode::FACE,
    //                                                                                             {-50, -50}));
    // firstLevel->save();
    saveAs("example2");
}
