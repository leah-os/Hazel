#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
	{

	}
	~ExampleLayer()
	{

	}
	
	void OnUpdate() override
	{
	}

	void OnEvent(Hazel::Event& event)
	{
		HZ_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		HZ_INFO("Sandbox started");
		PushLayer(new ExampleLayer());
		PushLayer(new Hazel::ImGuiLayer());
	}
	~Sandbox()
	{
		HZ_INFO("Sandbox term");
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}