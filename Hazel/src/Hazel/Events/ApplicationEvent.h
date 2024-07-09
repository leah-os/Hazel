#pragma once
#include "Event.h"

namespace Hazel
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window resize event: " << GetWidth() << ", " << GetHeight();
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window close event";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "App tick event";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "App Update Event";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "App Render Event";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
}