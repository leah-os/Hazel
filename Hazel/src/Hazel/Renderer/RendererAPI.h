#pragma once

#include <memory>
#include "Hazel/Model.h"
#include "VertexArray.h"


namespace Hazel
{
	class RendererAPI
	{
	public:
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& va) = 0;
		virtual void DrawArrays(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<HzModel>& mesh) = 0;

	public:
		enum class API {
			None = 0, OpenGL, Vulkan, DirectX12
		};
		static inline API GetAPI() { return s_API; }

	private:
		static API s_API;
	};

}