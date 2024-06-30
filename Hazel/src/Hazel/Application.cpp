#include "Application.h"
#include "Events/ApplicationEvent.h"

namespace Hazel {

	Application::Application()
	{
		;
	}

	Application::~Application()
	{
		;
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		HZ_CORE_INFO(e.ToString());
		while (true)
			;
	}
}