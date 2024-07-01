#pragma once

#include <GLFW/glfw3.h>
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"

namespace Hazel {
	class HZAPI Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	/* To be define in Client Application */
	Application* CreateApplication();

}