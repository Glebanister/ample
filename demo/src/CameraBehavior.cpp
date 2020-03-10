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
        camera.moveInViewDirection(-10);
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_w))
    {
        camera.moveInViewDirection(10);
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        camera.translate({0, -5, 0});
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        camera.translate({0, 5, 0});
    }
    camera.rotate({0, 1, 0}, game.eventManager->mouse()->getMouseXRel() / game.getWidth() * 3);
    camera.rotate({1, 0, 0}, -game.eventManager->mouse()->getMouseYRel() / game.getHeight() * 3);
}
