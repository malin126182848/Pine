#pragma once

#include "Window.h"
#include "globel.h"

struct GLFWwindow;

NAMESPACE_BEGIN(Engine);

class WindowsForm : public IWindow
{
public:
    WindowsForm(const WindowProps& props);
    virtual ~WindowsForm();

    void onUpdate() override;
    bool isRunning() override;

    inline unsigned int getWidth() const override
    {
        return 1;
    }
    inline unsigned int getHeight() const override
    {
        return 1;
    }

    inline void setEventCallback(const EventCallbackFn& callback) override
    {
        m_Data.eventCallback = callback;
    }

    void setVSync(bool enabled) override;
    bool isVSync() override;

private:
    virtual void init(const WindowProps& props);
    virtual void shutdown();

private:
    GLFWwindow* m_Window = nullptr;

    struct WindowData
    {
        std::string title;
        unsigned int width = 0;
        unsigned int height = 0;
        bool VSync = false;

        EventCallbackFn eventCallback;
    };

    WindowData m_Data;
};

NAMESPACE_END(Engine);
