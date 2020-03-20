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
    layer.addObject(object);
    layer.addObject(lamp);
    addLayer(layer);
    lamp.translate({-20, 20, -10});
}
