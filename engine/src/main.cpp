#include <cxxopts.hpp>

#include "Game2d.h"

int main(int argc, char **argv)
{
    cxxopts::Options options("ample-engine", "Ample project executor. Specify directory you want to run.");
    options.add_options()("p,path", "Specify project path", cxxopts::value<std::string>())("h,help", "Print usage");
    std::string projectName = "examples/demo2/";
    // try
    // {
    //     auto result = options.parse(argc, argv);
    //     if (result.count("help"))
    //     {
    //         std::cout << options.help() << std::endl;
    //         return 0;
    //     }
    //     if (!result.count("path"))
    //     {
    //         std::cout << "path is required" << std::endl;
    //         return 0;
    //     }
    //     projectName = result["path"].as<std::string>();
    // }
    // catch (const std::exception &e)
    // {
    //     std::cout << e.what() << std::endl;
    //     return 0;
    // }

    try
    {
        ample::game::game2d::Game2d("engine",
                                    0, 0,
                                    1920, 1080,
                                    ample::window::winpos::CENTERED_X | ample::window::winpos::CENTERED_Y,
                                    ample::window::FULLSCREEN,
                                    projectName)
            .loop();
    }
    catch (const ample::exception::Exception &ex)
    {
        ex.report();
        return 1;
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "Error occured" << std::endl;
        return 1;
    }

    return 0;
}
