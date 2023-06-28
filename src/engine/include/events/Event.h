#pragma once

#include "globel.h"
#include <concepts>
#include <functional>
#include <type_traits>

NAMESPACE_BEGIN(Engine)

#define BIT(x) 1 << x

enum class EventType
{
    etNone = 0,
    etWindowClose,
    etWindowResize,
    etWindowFocus,
    etWindowLastFocus,
    etWindowMoved,
    etAppTick,
    etAppUpdate,
    etAppRender,
    etKeyPressed,
    etKeyReleased,
    etMousePressed,
    etMouseReleased,
    etMouseMoved,
    etMouseScrolled,
};

enum class EventCategory
{
    ecNone = 0,
    ecApplication = BIT(0),
    ecInput = BIT(1),
    ecKeyboard = BIT(2),
    ecMouse = BIT(3),
    ecMouseButton = BIT(4),
};

#define DEFINE_EVENT_TYPE(type)                                                                                        \
    static EventType getStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::et##type;                                                                                      \
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

namespace detail {

template<typename R, typename ...As>
struct __function_traits_base {
    using function_type = std::function<R(As...)>;
    static const size_t nargs = sizeof...(As);
    using result_type = R;
	// 输入参数类型,i为从0开始的参数类型索引
    template <size_t i>
    using arg = typename std::tuple_element<i, std::tuple<As...>>::type;
};

template<typename F>
struct __function_traits;
template<typename F>
struct __function_traits<std::reference_wrapper<F>> : public __function_traits<F> {};
template<typename R, typename ...As>
struct __function_traits<R(*)(As...)> : public __function_traits_base<R, As...> {};
template<typename R, typename C, typename ...As>
struct __function_traits<R(C::*)(As...)> : public __function_traits_base<R, As...> {};
template<typename R, typename C, typename ...As>
struct __function_traits<R(C::*)(As...) const> : public __function_traits_base<R, As...> {};
template<typename F>
struct __function_traits : public __function_traits<decltype(&F::operator())> {};

}

template<typename F>
struct function_traits : public detail::__function_traits<std::decay_t<F>> {};

class EventDispatcher
{
    template <typename T> using EventFn = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event)
        : m_Event(event)
    {
        ;
    }

    template <typename Functor, typename T = std::remove_const_t<std::remove_reference_t<typename function_traits<Functor>::template arg<0>>>>
    requires requires(Functor&& func, T&& t) {
        requires std::convertible_to<T&, Event&>;
        requires std::invocable<decltype(std::remove_reference_t<T>::getStaticType)>;
        { func(t) } -> std::same_as<bool>;
    }
    bool dispatch(Functor&& func)
    {
        if (m_Event.getEventType() == std::remove_reference_t<T>::getStaticType())
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
