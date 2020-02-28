#include "DemoGame.h"
#include "WindowActivity.h"
#include "Exception.h"

int main()
{
    try
    {
        ample::window::Window window("DemoGame",
                                     0, 0,
                                     1920, 1080,
                                     ample::window::winpos::CENTERED_X | ample::window::winpos::CENTERED_Y,
                                     ample::window::FULLSCREEN);
        auto activity = DemoGame(window);
        activity.loop();
    }
    catch (const ample::exception::Exception &ex)
    {
        ex.report();
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Error occured" << std::endl;
    }
    return 0;
}
