#pragma once

#include "globel.h"
#include <functional>

NAMESPACE_BEGIN(Engine)

#define BIT(x) 1 << x

enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLastFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    MousePressed,
    MouseReleased,
    MouseMoved,
    MouseScrolled,
};

enum class EventCategory
{
    None = 0,
    ecApplication = BIT(0),
    ecInput = BIT(1),
    ecKeyboard = BIT(2),
    ecMouse = BIT(3),
    ecMouseButton = BIT(4),
};

#define DEFINE_EVENT_TYPE(type)                                                                                        \
    static EventType getStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::##type;                                                                                      \
    }                                                                                                                  \
    virtual EventType getEventType() const override                                                                    \
    {                                                                                                                  \
        return getStaticType();                                                                                        \
    }                                                                                                                  \
    virtual const char* getName() const override                                                                       \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

class ENGINE_API Event
{
    friend class EventDispatcher;

public:
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual int getCategoryFlags() const = 0;
    virtual std::string toString() const
    {
        return getName();
    };

    inline bool isInCategory(EventCategory category)
    {
        return getCategoryFlags() & static_cast<int>(category);
    }

protected:
    bool m_Handled = false;
};

class EventDispatcher
{
    template <typename T> using EventFn = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event)
        : m_Event(event)
    {
    }

    template <typename T> bool dispatch(EventFn<T> func)
    {
        if (m_Event.getEventType() == T::getStaticType())
        {
            m_Event.m_Handled = func(*(T*)&m_Event);
            return true;
        }
        return false;
    }

private:
    Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.toString();
}

NAMESPACE_END(Engine)
