#include "CameraBehavior.h"
#include "Debug.h"

CameraBehavior::CameraBehavior(ample::window::WindowActivity &game, ample::graphics::Camera &camera)
    : game(game), camera(camera) {}

void CameraBehavior::onActive()
{
    ample::activity::Activity::onActive();
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        camera.translateEye({5, 0, 0});
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        camera.translateEye({-5, 0, 0});
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_s))
    {
        camera.translateEye({0, 0, 5});
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_w))
    {
        camera.translateEye({0, 0, -5});
        DEBUG(camera.getEyeX());
        DEBUG(camera.getEyeY());
        DEBUG(camera.getEyeZ());
        DEBUG('\n');
    }
}
