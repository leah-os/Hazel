/*
#pragma once

#include <GLFW/glfw3.h>
#include "Window.h"

namespace Hazel {

	class HZAPI UnixWindow : public Window
	{
	public:
		UnixWindow(const WindowProps& props);
		virtual ~UnixWindow();

		virtual void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline  void SetEventCallback(EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

	private:
		void Init(const WindowProps& props);
		void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			EventCallbackFn EventCallback;
			bool VSync;
		};
		WindowData m_Data;
	};

}
*/