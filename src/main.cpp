#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <stdexcept>

#include "Activity.h"
#include "EventManager.h"
#include "Logger.h"
#include "Window.h"

class A : public control::KeyHandler
{
public:
    A(char letter)
        : letter(letter) {}

    void onKeyDown() override
    {
        std::cout << letter << " down" << std::endl;
    }

    void onKeyUp() override
    {
        std::cout << letter << " up!" << std::endl;
    }
private:
    const char letter;
};

int main()
{
    auto log = os::Logger();
    auto window = os::Window("Hello, World!",
                             0, 0,
                             0, 0,
                             os::winpos::UNDEFINED,
                             os::winmode::MAXIMIZED);
    auto a = A('A');
    auto b = A('B');
    auto c = A('C');
    auto d = A('D');
    auto e = A('E');
    auto act = activity::WindowActivity(&window);
    act.eventManager->addKeyHandler(control::KEY_a, &a);
    act.eventManager->addKeyHandler(control::KEY_b, &b);
    act.eventManager->addKeyHandler(control::KEY_c, &c);
    act.eventManager->addKeyHandler(control::KEY_d, &d);
    act.eventManager->addKeyHandler(control::KEY_e, &e);
    act.mainLoop();

    return 0;
}
