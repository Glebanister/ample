#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "KeyboardControlCamera.h"
#include "WorldObject2d.h"
#include "WorldDistanceJoint.h"
#include "Debug.h"
#include "RegularPolygon.h"
#include <memory>
#include <vector>

#include <fstream>
#include <sstream>

DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    layer.addCamera(camera);
    layer.addObject(object);
    addLayer(layer);
}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
}
