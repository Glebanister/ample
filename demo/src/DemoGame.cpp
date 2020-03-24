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
    for (size_t i = 0; i < 7; ++i)
    {
        smooth.emplace_back(std::make_unique<ample::graphics::GraphicalObject2d>(ample::geometry::RegularPolygon<float>(10,
                                                                                                                        (i + 1) * 3),
                                                                                 10,
                                                                                 0));
        smooth[i]->translate({30 * i, 0, 0});
        layer.addObject(*smooth[i]);
    }
    for (size_t i = 0; i < 7; ++i)
    {
        rough.emplace_back(std::make_unique<ample::graphics::GraphicalObject2d>(ample::geometry::RegularPolygon<float>(10,
                                                                                                                       (i + 1) * 3),
                                                                                10,
                                                                                0));
        rough[i]->translate({30 * i, 50, 0});
        layer.addObject(*rough[i]);
    }
    layer.addObject(camera.getLamp());
    addLayer(layer);
    _window.disableCursor();
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    _window.moveCursor(0, 0);
}
