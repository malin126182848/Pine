#ifndef PINE_APPLICATION_H
#define PINE_APPLICATION_H

#include "Window.h"
#include "globel.h"

NAMESPACE_BEGIN(Engine)

class ENGINE_API Application
{
public:
    Application();
    virtual ~Application() = default;

    void run();

private:
    std::unique_ptr<IWindow> m_Window;
    bool m_Running = true;
};

NAMESPACE_END(Engine)
#endif
