#include "WindowsForm.h"
#include "GLFW/glfw3.h"
#include "Log.h"
#include <cassert>

NAMESPACE_BEGIN(Engine);

static bool s_GLFWInitialized = false;

IWindow* IWindow::create(const WindowProps& props)
{
    return new WindowsForm(props);
}

WindowsForm::WindowsForm(const WindowProps& props)
{
    init(props);
}

WindowsForm::~WindowsForm()
{
    shutdown();
}

void WindowsForm::init(const WindowProps& props)
{
    m_Data.title = props.title;
    m_Data.width = props.width;
    m_Data.height = props.height;

    PN_LOG_APP_INFO("creating window {0} ({1}, {2})", props.title, props.width, props.height);

    if (!s_GLFWInitialized)
    {
        int success = glfwInit();
        if (success)
        {
            PN_LOG_APP_ERROR("could not initialize GLFW");
        }

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    setVSync(true);
}

void WindowsForm::shutdown()
{
    glfwDestroyWindow(m_Window);
}

void WindowsForm::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void WindowsForm::setVSync(bool enabled)
{
    if (enabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
    m_Data.VSync = enabled;
}

bool WindowsForm::isVSync()
{
    return m_Data.VSync;
}

NAMESPACE_END(Engine);
