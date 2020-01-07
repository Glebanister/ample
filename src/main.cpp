#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <stdexcept>

#include "Activity.h"
#include "EventManager.h"
#include "Window.h"
#include "WindowActivity.h"

class HipHop : public control::KeyHandler
{
    void onKeyDown() override
    {
        std::cout << "Hip" << std::endl;
    }

    void onKeyUp() override
    {
        std::cout << "Hop!" << std::endl;
    }
};

class MouseMotion : public control::EventHandler
{
    void handleEvent(const control::Event &event) override
    {
        std::cout << event.wheel.x << ' ' << event.wheel.y << std::endl;
    }
};

int main()
{
    auto window = window::Window(512, 256,
                                     "Hello, World!",
                                     window::mode::RESIZABLE);
    auto act = window::WindowActivity(&window);
    auto hipHop = HipHop();
    auto mouse = MouseMotion();

    act.eventManager->addKeyHandler(control::KEY_h, &hipHop);
    act.eventManager->addEventHandler(control::MOUSEWHEEL, &mouse);
    act.run();

    return 0;
}
