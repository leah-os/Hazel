#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Events/Event.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool m_Running = true;
		float m_LastFrameTime = 0.0f;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
	private:
		bool OnWindowClose(Event& e);
	public:
		static Application* s_Instance;
	};

	/* To be define in Client Application */
	Application* CreateApplication();

}