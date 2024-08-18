#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& va) override;
	};

}