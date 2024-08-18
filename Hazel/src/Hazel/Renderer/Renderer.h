#pragma once

#include "Camera.h"
#include "RendererAPI.h"
#include "Hazel/Core/Base.h"
#include "Hazel/Core/Model.h"

namespace Hazel {

	class Renderer
	{
	public:
		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();

		static void Clear();
		static void Submit(const Ref<VertexArray>& va);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	};

}