#ifndef PINE_WINDOW_H
#define PINE_WINDOW_H

#include "Event.h"
#include "globel.h"

NAMESPACE_BEGIN(Engine);

struct WindowProps
{
    std::string title = "Pine Engine";
    unsigned int width = 1280;
    unsigned int height = 720;
};

class ENGINE_API IWindow
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~IWindow() = default;

    virtual void onUpdate() = 0;
    virtual bool isRunning() = 0;

    virtual unsigned int getWidth() const = 0;
    virtual unsigned int getHeight() const = 0;

    virtual void setEventCallback(const EventCallbackFn& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() = 0;

    static IWindow* create(const WindowProps& props = WindowProps());
};

NAMESPACE_END(Engine);

#endif
