#pragma once

#include <memory>
#include "VertexArray.h"
#include "Hazel/Core/Model.h"


namespace Hazel
{
	class RendererAPI
	{
	public:
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& va) = 0;
	public:
		enum class API {
			None = 0, OpenGL, Vulkan, DirectX12
		};
		static inline API GetAPI() { return s_API; }

	private:
		static API s_API;
	};

}