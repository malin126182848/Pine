#include "Application.h"

#include <iostream>

namespace Engine
{
    Application::Application()
    {
    }

    void Application::run()
    {
        std::cout << "is app run: hello world" << std::endl;
    }
} // namespace Engine
