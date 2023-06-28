#ifndef MOUSEEVENT_H_
#define MOUSEEVENT_H_

#include "Event.h"
#include <sstream>

NAMESPACE_BEGIN(Engine);
class MouseMovedEvent : public Event
{
public:
    DEFINE_EVENT_TYPE(MouseMoved);

    int getCategoryFlags() const override
    {
        return static_cast<int>(EventCategory::ecMouse);
    }

    std::string toString() const override
    {
        // Create a string with represents
        std::stringstream ss;
        ss << "MouseMovedEvent: xOffset = " << GetXOffset() << ", yOffset = " << GetYOffset();
        return ss.str();
    }

    inline int GetXOffset() const
    {
        return m_xOffset;
    }

    inline int GetYOffset() const
    {
        return m_yOffset;
    }

private:
    int m_xOffset = 0;
    int m_yOffset = 0;
};

NAMESPACE_END(Engine);
#endif