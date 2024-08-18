#pragma once

#include <string>
#include "Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel {
	class Layer
	{
	public:
		Layer(const std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}