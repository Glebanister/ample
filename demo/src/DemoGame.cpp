#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "DemoGame.h"
#include "RegularPolygon.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::game::game2d::Game2d(window)
{
    ample::graphics::GraphicalObject2dRaw sample1{ample::geometry::RegularPolygon<float>(50, 8),
                                                  10.0,
                                                  20.0,
                                                  "../../demo/textures/lena512.png",
                                                  {512, 512},
                                                  {0, 0},
                                                  {
                                                      ample::graphics::textureMode::STRETCH,
                                                      ample::graphics::textureMode::STRETCH,
                                                  },
                                                  ample::graphics::channelMode::RGB,
                                                  "../../demo/textures/lena512.png",
                                                  {512, 512},
                                                  {0, 0},
                                                  {
                                                      ample::graphics::textureMode::STRETCH,
                                                      ample::graphics::textureMode::STRETCH,
                                                  },
                                                  ample::graphics::channelMode::RGB,
                                                  ample::graphics::normalsMode::FACE};
    ample::graphics::GraphicalObject2dRaw sample2{ample::geometry::RegularPolygon<float>(10, 8),
                                                  10.0,
                                                  20.0,
                                                  "../../demo/textures/wood.jpg",
                                                  {2000, 1333},
                                                  {0, 0},
                                                  {
                                                      ample::graphics::textureMode::STRETCH,
                                                      ample::graphics::textureMode::STRETCH,
                                                  },
                                                  ample::graphics::channelMode::RGBA,
                                                  "../../demo/textures/LAND.BMP",
                                                  {1024, 768},
                                                  {0, 0},
                                                  {
                                                      ample::graphics::textureMode::STRETCH,
                                                      ample::graphics::textureMode::STRETCH,
                                                  },
                                                  ample::graphics::channelMode::RGB,
                                                  ample::graphics::normalsMode::FACE};
    object1 = std::make_unique<ample::graphics::GraphicalObject2d>(sample1);
    object2 = std::make_unique<ample::graphics::GraphicalObject2d>(sample2);
    object2->translate({-30, 0, -30});
    _window.disableCursor();
    auto level = createLevel(0, 10.0f, 0.5f);
    // level.frontSlice().addObject(*object1);
    // level.frontSlice().addObject(*object2);
}
