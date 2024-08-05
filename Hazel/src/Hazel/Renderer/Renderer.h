#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& va);
		static void Submit(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<HzModel>& mesh);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}