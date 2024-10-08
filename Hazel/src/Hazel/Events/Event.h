#pragma once

#include <string>
#include <sstream>
#include <functional>

#include "Hazel/Core/Base.h"

namespace Hazel {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		AppTick, AppUpdate, AppRender,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCategory {
		None = 0,
		EventCategoryApplication	=	BIT(0),
		EventCategoryInput			=	BIT(1),
		EventCategoryKeyboard		=	BIT(2),
		EventCategoryMouse			=	BIT(3),
		EventCategoryMouseButton	=	BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		inline bool IsHandled() const { return m_Handled; }

	protected:
		bool m_Handled = false;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		os << e.ToString();
		return os;
	}

	class EventDispatcher {
	public:
		EventDispatcher(Event& e)
			: m_Event(e) {}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

}