#pragma once

#include "Core.h"

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