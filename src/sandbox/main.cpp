#include "Application.h"
#include "Log.h"

#include <iostream>
#include <memory>

#ifdef _WIND
int ll = 0;
#else
int qq = 0;
#endif

using namespace std;

class SandboxApp : public Engine::Application
{
public:
    SandboxApp() = default;
    ~SandboxApp() = default;
};

int main(int argc, char** argv)
{
    PN_LOG_DEBUG("Initialized log!");
    int a = 34;
    PN_LOG_APP_INFO("Hello, var = {0}", a);

    std::unique_ptr<SandboxApp> app = std::make_unique<SandboxApp>();
    app->run();
    return 0;
}
