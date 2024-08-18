#include "Renderer.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: HZ_CORE_ASSERT(false && "RendererAPI::NONE is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		HZ_CORE_ASSERT(false && "Unknown Renderer API");
		return nullptr;
	}
}