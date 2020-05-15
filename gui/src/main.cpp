#include <iostream>
#include <imgui.h>
#include <ample/SDLEnvironment.h>
#include <ample/Window.h>
#include <ample/Clock.h>
#include <ample/WindowActivity.h>

#include "AmpleGui.h"

int main()
{
    ample::gui::AmpleGui().loop();

    return 0;
}
