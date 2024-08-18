#pragma once

#include "RendererAPI.h"

namespace Hazel
{
	class RenderCommand
	{
	public:
		static inline void Clear()
		{
			s_RendererAPI->Clear();
		}
		static inline void DrawIndexed(const Ref<VertexArray>& va)
		{
			s_RendererAPI->DrawIndexed(va);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}