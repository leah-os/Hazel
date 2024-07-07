#pragma once

#include "Hazel/Layer.h"

#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {

	class HZAPI ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnKeyPressedCallback(KeyPressedEvent& event);
		bool OnKeyReleasedCallback(KeyReleasedEvent& event);
		bool OnKeyTypedCallback(KeyTypedEvent& event);
		bool OnMouseScrolledCallback(MouseScrolledEvent& event);
		bool OnMouseButtonPressedCallback(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedCallback(MouseButtonReleasedEvent& event);
		bool OnMouseMovedCallback(MouseMovedEvent& event);
		bool OnWindowResizeCallback(WindowResizeEvent& event);

	private:
		float m_Time = 0.0f;
	};

}