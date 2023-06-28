#include "Application.h"
#include "pch.h"

#include <glad/gl.h>
#include <memory>
#include <GLFW/glfw3.h>

#include "linmath.h"

NAMESPACE_BEGIN(Engine);

Application::Application()
{
    m_Window = std::unique_ptr<IWindow>(IWindow::create());
}

void Application::run()
{
    while (m_Window->isRunning())
    {
        m_Window->onUpdate();
    }
}

NAMESPACE_END(Engine);
