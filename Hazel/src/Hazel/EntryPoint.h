#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application *Hazel::CreateApplication();

int main(int argc, char **argv)
{
	Hazel::Log::Init();

	HZ_CORE_INFO("Hazel Engine");

	HZ_CRITICAL("Fatal in application");


	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif
