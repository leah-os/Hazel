#include "Buffer.h"
#include "Renderer.h"
#include "Hazel/Core.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Hazel
{
	
	VertexBuffer* VertexBuffer::Create(const void* data, unsigned int size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: HZ_CORE_ASSERT(false && "RendererAPI::NONE is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(data, size);
		}

		HZ_CORE_ASSERT(false && "Unknown Renderer API");
		return nullptr;

	}

	IndexBuffer* IndexBuffer::Create(const unsigned int* indices, unsigned int size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: HZ_CORE_ASSERT(false && "RendererAPI::NONE is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		HZ_CORE_ASSERT(false && "Unknown Renderer API");
		return nullptr;
	}

}