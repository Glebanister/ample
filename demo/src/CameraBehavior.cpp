#include "CameraBehavior.h"
#include "Debug.h"

CameraBehavior::CameraBehavior(ample::window::WindowActivity &game, ample::graphics::Camera &camera)
    : game(game), camera(camera) {}

void CameraBehavior::onActive()
{
    ample::activity::Activity::onActive();
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        camera.translate({5, 0, 0});
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        camera.translate({-5, 0, 0});
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_s))
    {
        camera.translateEye({0, 0, -5});
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_w))
    {
        camera.translateEye({0, 0, 5});
    }

    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        camera.translate({0, -5, 0});
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        camera.translate({0, 5, 0});
    }
}
