#include "Buffer.h"
#include "Hazel/Core.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	
	VertexBuffer* VertexBuffer::Create(void* data, unsigned int size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::None: HZ_CORE_ASSERT(false && "RendererAPI::NONE is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(data, size);
		}

		HZ_CORE_ASSERT(false && "Unknown Renderer API");
		return nullptr;

	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::None: HZ_CORE_ASSERT(false && "RendererAPI::NONE is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		HZ_CORE_ASSERT(false && "Unknown Renderer API");
		return nullptr;
	}

}