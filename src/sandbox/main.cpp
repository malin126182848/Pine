#include "Application.h"

#include <iostream>
#include <memory>

class SandboxApp : public Engine::Application
{
public:
    SandboxApp() = default;
    ~SandboxApp() = default;
};

int main(int argc, char** argv)
{
    int a = 0;
    int c = a + 1;
    std::unique_ptr<SandboxApp> app = std::make_unique<SandboxApp>();
    app->run();
    return 0;
}
