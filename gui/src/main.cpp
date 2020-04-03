#include <iostream>
#include <imgui.h>
#include <imgui_sdl.h>
#include <ample/SDLEnvironment.h>
#include <ample/Window.h>
#include <ample/Clock.h>
#include <ample/WindowActivity.h>

#include "ImguiActivity.h"

int main()
{
    ample::window::Window window{
        "ample gui",
        0,
        0,
        1920 / 1.5,
        1080 / 1.5,
        ample::window::CENTERED_X | ample::window::CENTERED_Y,
        ample::window::MINIMIZED | ample::window::RESIZABLE,
    };
    ample::gui::ImguiActivity ampleGui{window};
    ampleGui.loop();

    return 0;
}
