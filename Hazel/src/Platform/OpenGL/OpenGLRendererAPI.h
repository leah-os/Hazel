#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& va) override;
		virtual void DrawArrays(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<HzModel>& mesh) override;
	};

}