#pragma once

#include "RendererAPI.h"

namespace Hazel
{
	class RenderCommand
	{
	public:
		static inline void DrawIndexed(const std::shared_ptr<VertexArray>& va)
		{
			s_RendererAPI->DrawIndexed(va);
		}
		static inline void DrawArrays(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<HzModel>& mesh)
		{
			s_RendererAPI->DrawArrays(va, mesh);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}