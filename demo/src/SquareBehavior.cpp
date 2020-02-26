#include "SquareBehavior.h"

SquareBehavior::SquareBehavior(ample::window::WindowActivity &game, ample::graphics::ScreenObject &object)
    : game(game), object(object) {}

void SquareBehavior::onActive()
{
    if (game.eventManager->keyboard()->isKeyDown(ample::control::ARROW_LEFT))
    {
        object.rotate(0, 0, 1);
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::ARROW_RIGHT))
    {
        object.rotate(0, 0, -1);
    }
}
