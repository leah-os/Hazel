#pragma once

#if defined HZ_PLATFORM_WINDOWS || HZ_PLATFORM_UNIX

extern Hazel::Application *Hazel::CreateApplication();

int main(int argc, char **argv)
{
	Hazel::Log::Init();

	HZ_CORE_INFO("Welcome to Hazel Engine");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#else
#error "Hazel support`s only Windows and Unix!"
#endif