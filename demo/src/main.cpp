#include "DemoGame.h"
#include "WindowActivity.h"

int main()
{
    ample::window::Window window("DemoGame",
                      0, 0,
                      1920, 1080,
                      ample::window::winpos::CENTERED_X | ample::window::winpos::CENTERED_Y,
                      ample::window::FULLSCREEN);
    auto activity = DemoGame(window);
    activity.loop();
    return 0;
}
