#pragma once

namespace Hazel {

	enum class RendererAPI {
		None = 0, OpenGL, Vulkan, DirectX12
	};

	class Renderer
	{
	public:
		static inline RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};

}