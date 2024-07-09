#include <Hazel.h>

#include "imgui.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
	{
		HZ_INFO("ExampleLayer started");
	}
	~ExampleLayer()
	{
		HZ_INFO("ExampleLayer terminated");
	}
	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Example Layer");
		ImGui::End();
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
		HZ_INFO("Sandbox terminated!");
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}