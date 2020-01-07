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

int main()
{
    window::Window window = window::Window(512, 256,
                                           "First one!",
                                           window::mode::RESIZABLE);
    auto a = A();
    auto act = window::WindowActivity(&window);
    act.eventManager->addKeyHandler(control::KEY_a, &a);
    act.run();

    return 0;
}
