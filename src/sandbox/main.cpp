#include "Application.h"
#include "Log.h"

#include <iostream>
#include <memory>

using namespace std;

class SandboxApp : public Engine::Application
{
public:
    SandboxApp() = default;
    ~SandboxApp() = default;
};

int main(int argc, char** argv)
{
    std::unique_ptr<SandboxApp> app = std::make_unique<SandboxApp>();
    app->run();
    return 0;
}
