/*
#include "UnixWindow.h"

namespace Hazel {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new UnixWindow(props);
	}

	UnixWindow::UnixWindow(const WindowProps& props)
	{
		Init(props);
	}

	UnixWindow::~UnixWindow()
	{
		Shutdown();
	}

	void UnixWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void UnixWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} {1}x{2}", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Couldn`t initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), 0, 0);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void UnixWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void UnixWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}

	bool UnixWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
*/