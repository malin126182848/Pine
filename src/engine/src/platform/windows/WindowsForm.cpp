#include "WindowsForm.h"
#include "Event.h"
#include "GLFW/glfw3.h"
#include <glad/gl.h>
#include "Log.h"
#include "MouseEvent.h"

NAMESPACE_BEGIN(Engine);

static bool s_GLFWInitialized = false;

IWindow* IWindow::create(const WindowProps& props)
{
    return new WindowsForm(props);
}

WindowsForm::WindowsForm(const WindowProps& props)
{
    init(props);
    MouseMovedEvent ev;
    EventDispatcher d(ev);
    d.dispatch([this](const MouseMovedEvent& ev) -> bool {
        int i = m_Data.height;
        return false;
    });
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

    glfwSetErrorCallback([](int error, const char* description) {
        PN_LOG_APP_ERROR("error code: {0} , msg: {1}", error, description);
    });

    if (!s_GLFWInitialized)
    {
        if (!glfwInit())
        {
            PN_LOG_APP_ERROR("could not initialize GLFW");
            return;
        }
        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        PN_LOG_APP_ERROR("could not create window");
        glfwTerminate();
        return;
    }

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    gladLoadGL(glfwGetProcAddress);
    setVSync(true);
}

void WindowsForm::shutdown()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void WindowsForm::onUpdate()
{
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

bool WindowsForm::isRunning()
{
    return !glfwWindowShouldClose(m_Window);
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
