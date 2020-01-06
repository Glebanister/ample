#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <cassert>

#include "Storage.h"
#include "Condition.h"
#include "Activity.h"
#include "EventHandler.h"
#include "EventManager.h"

class W_handler : control::KeyHandler
{
public:
    void onKeyUp() override
    {
        std::cout << "Hip" << std::endl;
    }
    void onKeyDown() override
    {
        std::cout << "Hop!" << std::endl;
    }
};

int main()
{
    W_handler *w = new W_handler;
    return 0;
}
