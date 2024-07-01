#include <Hazel.h>

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		HZ_INFO("Sandbox started");
	}
	~Sandbox()
	{
		HZ_INFO("Sandbox terminated");
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}