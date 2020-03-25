#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "KeyboardControlCamera.h"
#include "WorldObject2d.h"
#include "WorldDistanceJoint.h"
#include "Debug.h"
#include "RegularPolygon.h"

DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    layer.addCamera(camera);
    ample::graphics::GraphicalObject2dRaw sample1{ample::geometry::RegularPolygon<float>(10, 8),
                                                  10.0,
                                                  20.0,
                                                  "../../demo/textures/LAND.BMP",
                                                  {1024, 768},
                                                  {0, 0},
                                                  {
                                                      ample::graphics::textureMode::STRETCH,
                                                      ample::graphics::textureMode::STRETCH,
                                                  },
                                                  "../../demo/textures/lena512.png",
                                                  {512, 512},
                                                  {0, 0},
                                                  {
                                                      ample::graphics::textureMode::STRETCH,
                                                      ample::graphics::textureMode::STRETCH,
                                                  },
                                                  ample::graphics::normalsMode::FACE};
    ample::graphics::GraphicalObject2dRaw sample2{ample::geometry::RegularPolygon<float>(10, 8),
                                                  10.0,
                                                  20.0,
                                                  "../../demo/textures/lena512.png",
                                                  {512, 512},
                                                  {0, 0},
                                                  {
                                                      ample::graphics::textureMode::STRETCH,
                                                      ample::graphics::textureMode::STRETCH,
                                                  },
                                                  "../../demo/textures/LAND.BMP",
                                                  {1024, 768},
                                                  {0, 0},
                                                  {
                                                      ample::graphics::textureMode::STRETCH,
                                                      ample::graphics::textureMode::STRETCH,
                                                  },
                                                  ample::graphics::normalsMode::FACE};
    object1 = std::make_unique<ample::graphics::GraphicalObject2d>(sample1);
    object2 = std::make_unique<ample::graphics::GraphicalObject2d>(sample2);
    layer.addObject(*object1);
    layer.addObject(*object2);
    layer.addObject(camera.getLamp());
    addLayer(layer);
    object2->translate({-30, 0, 0});
    _window.disableCursor();
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    _window.moveCursor(0, 0);
}
