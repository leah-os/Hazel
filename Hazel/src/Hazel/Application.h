#pragma once

#include "Core.h"
#include "Log.h"
#include "Events/Event.h"

namespace Hazel {
	class HZAPI Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	/* To be define in Client Application */
	Application* CreateApplication();
}