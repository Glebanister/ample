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

class A : public control::KeyHandler
{
    void onKeyDown() override
    {
        std::cout << "A down" << std::endl;
    }

    void onKeyUp() override
    {
        std::cout << "A up!" << std::endl;
    }
};

class B : public control::KeyHandler
{
    void onKeyDown() override
    {
        std::cout << "B down" << std::endl;
    }

    void onKeyUp() override
    {
        std::cout << "B up!" << std::endl;
    }
};

class C : public control::KeyHandler
{
    void onKeyDown() override
    {
        std::cout << "C down" << std::endl;
    }

    void onKeyUp() override
    {
        std::cout << "C up!" << std::endl;
    }
};

class MouseMotion : public control::EventHandler
{
    void handleEvent(const control::Event &event) override
    {
        std::cout << event.wheel.x << ' ' << event.wheel.y << std::endl;
    }
};

// TODO sdgsdf

int main()
{
    auto window = window::Window(512, 256,
                                     "Hello, World!",
                                     window::mode::MAXIMIZED |
                                     window::mode::RESIZABLE);
    // auto window2 = window::Window(512, 256,
    //                                  "Second one!",
    //                                  window::mode::RESIZABLE);
    auto act = window::WindowActivity(&window);
    // auto act2 = window::WindowActivity(&window2);
    auto a = A();
    auto b = B();
    auto c = C();
    auto mouse = MouseMotion();

    act.eventManager->addKeyHandler(control::KEY_a, &a);
    act.eventManager->addKeyHandler(control::KEY_b, &b);
    act.eventManager->addKeyHandler(control::KEY_c, &c);
    act.eventManager->addEventHandler(control::MOUSEWHEEL, &mouse);
    act.run();
    // act2.run();

    return 0;
}
